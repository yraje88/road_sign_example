#include "ensemble.h"
#include "ensemble_validate.h"
#include <string.h>
#include <stdio.h>

// Global variables
int numTrainSamples = 0;

// Neural networks for CNNs
network *cnn[NUM_NETS];

// Configuration files
char *tmr_data[NUM_NETS] = {"data/tmr.data"};
char *tmr_cfg[NUM_NETS] = {"data/tmr.cfg"};
char *tmr_weights[NUM_NETS] = {"backup/tmr.weights"};

// Data storage structs
load_args largs[NUM_NETS];
data dbuffer[NUM_NETS];
pthread_t lthreads[NUM_NETS];
char **img_paths[NUM_NETS];
char **class_labels[NUM_NETS];
char *backup_directory[NUM_NETS];
char *base[NUM_NETS];
int epochs[NUM_NETS];

// Network loss
float average_loss[NUM_NETS];

// Network output 
float predictions[NUM_NETS][NUM_CLASSES];
int pred_indexes[NUM_NETS][TOPK];

// Ensemble data storage
float topk_accuracy[NUM_NETS][TOPK];

// Initialisation functions
void initNets()
{
    srand(time(0));
    for(int i = 0; i < NUM_NETS; i++)
    {
        base[i] = basecfg(tmr_cfg[i]);
        cnn[i] = load_network(tmr_cfg[i], NULL, 0);
    }
    
}
void destructNets()
{
    for(int i = 0; i < NUM_NETS; i++)
    {
        free_network(cnn[i]);
    }
}

void initTrainData()
{
    for(int i = 0; i < NUM_NETS; i++)
    {
        cnn[i]->train = 1;

        average_loss[i] = -1;

        int imgs = cnn[i]->batch * cnn[i]->subdivisions;

        printf("Learning Rate: %g, Momentum: %g, Decay: %g\n", cnn[i]->learning_rate, cnn[i]->momentum, cnn[i]->decay);
        list *options = read_data_cfg(tmr_data[i]);

        backup_directory[i] = option_find_str(options, "backup", "/backup/");
        int tag = option_find_int_quiet(options, "tag", 0);
        char *label_list = option_find_str(options, "labels", "data/labels.list");
        char *train_list = option_find_str(options, "train", "data/train.list");
        char *tree = option_find_str(options, "tree", 0);
        if (tree) cnn[i]->hierarchy = read_tree(tree);
        int classes = option_find_int(options, "classes", 2);

        char **labels = 0;
        if(!tag){
            labels = get_labels(label_list);
        }
        list *plist = get_paths(train_list);
        char **paths = (char **)list_to_array(plist);
        printf("%d\n", plist->size);
        int N = plist->size;

        largs[i].w = cnn[i]->w;
        largs[i].h = cnn[i]->h;
        largs[i].threads = 32;
        largs[i].hierarchy = cnn[i]->hierarchy;

        largs[i].min = cnn[i]->min_ratio*cnn[i]->w;
        largs[i].max = cnn[i]->max_ratio*cnn[i]->w;
        printf("%d %d\n", largs[i].min, largs[i].max);
        largs[i].angle = cnn[i]->angle;
        largs[i].aspect = cnn[i]->aspect;
        largs[i].exposure = cnn[i]->exposure;
        largs[i].saturation = cnn[i]->saturation;
        largs[i].hue = cnn[i]->hue;
        largs[i].size = cnn[i]->w;

        largs[i].paths = paths;
        largs[i].classes = classes;
        largs[i].n = imgs;
        largs[i].m = N;
        largs[i].labels = labels;
        if (tag){
            largs[i].type = TAG_DATA;
        } else {
            largs[i].type = CLASSIFICATION_DATA;
        }

        largs[i].d = &dbuffer[i]; 
        lthreads[i] = load_data(largs[i]);
    }
}
void initValidData()
{
    for(int i = 0; i < NUM_NETS; i++)
    {
        set_batch_network(cnn[i], 1);
        list *options = read_data_cfg(tmr_data[i]);

        char *label_list = option_find_str(options, "labels", "data/labels.list");
        char *valid_list = option_find_str(options, "valid", "data/train.list");

        class_labels[i] = get_labels(label_list);
        list *plist = get_paths(valid_list);

        img_paths[i] = (char **)list_to_array(plist);
        numTrainSamples = plist->size;
        free_list(plist);
    }
}
void destructData()
{
    for(int i = 0; i < NUM_NETS; i++)
    {
        free_ptrs((void**)class_labels[i], NUM_CLASSES);
        free_ptrs((void**)img_paths[i], numTrainSamples);
    }
}

// Forward propagation during training
float forwardTrainTickCNN(int net)
{
    setSeen(net);

    // printf("Forward, net in bounds: %d\n", net);
    pthread_join(lthreads[net], 0);
    lthreads[net] = load_data(largs[net]);

    int batch = cnn[net]->batch;
    get_next_batch(*largs[net].d, batch, 0, cnn[net]->input, cnn[net]->truth);

    forward_network(cnn[net]);

    float loss = (*cnn[net]->cost)/batch;
    if(average_loss[net] == -1) average_loss[net] = loss;
    average_loss[net] = average_loss[net]*.9 + loss*.1;

    return loss;
}

// Back-propagation during training
void backwardTrainTickCNN(int net)
{
    // printf("Backward net in bounds: %d\n", net);
    backward_network(cnn[net]);
}

// Update network after back-propagation
void updateTrainTickCNN(int net)
{
    // printf("Update net in bounds: %d\n", net);
    update_network(cnn[net]);   
}

// Forward propagation during validation
void forwardValidTickCNN(int net, int img)
{
    int *indexes = calloc(TOPK, sizeof(int));

    image im = load_image_stb(img_paths[net][img], 3);
    
    float *pred = network_predict(cnn[net], im.data);
    top_k(pred, NUM_CLASSES, TOPK, indexes);

    for(int i = 0; i < NUM_CLASSES; i++)
    {
        predictions[net][i] = pred[i];
    }
    for(int i = 0; i < TOPK; i++)
    {
        pred_indexes[net][i] = indexes[i];
    }

    free_image(im);
}

// Ensemble functions
void updateOutput(int img)
{
    int class = -1;
    char *path = img_paths[0][img];
    for(int j = 0; j < NUM_CLASSES; ++j){
        if(strstr(path, class_labels[0][j])){
            class = j;
            break;
        }
    }

    int *indexes = calloc(TOPK, sizeof(int));

    for(int i = 0; i < NUM_NETS; i++)
    {
        for(int j = 0; j < TOPK; j++)
        {
            if(pred_indexes[i][j] == class) 
            {
                for(int k = j; k < TOPK; k++)
                    topk_accuracy[i][k] += 1;
            }
        }
    }   
}
void runValidTest()
{
    printf("========== RESULTS ==========\n");
    float avg[TOPK];
    for(int i = 0; i < NUM_NETS; i++)
    {
        printf("CNN %d: ", i); 
        for(int j = 0; j < TOPK; j++)
        {
            avg[j] += topk_accuracy[i][j] / numTrainSamples;
            printf("TOP %d: %f; ", j + 1, topk_accuracy[i][j] / numTrainSamples);
        }
        printf("\n");
    }
}


// Helper functions
void tryBackup()
{
    for(int i = 0; i < NUM_NETS; i++)
    {
        if(*cnn[i]->seen/largs[i].m > epochs[i])
        {
            epochs[i] = *cnn[i]->seen/largs[i].m;
            char buff[256];
            sprintf(buff, "%s/%s_%d.weights", backup_directory[i], base[i], epochs[i]);
            save_weights(cnn[i], buff);
        }
        else if(maxEpochs(i))
        {
            char buff[256];
            sprintf(buff, "%s/%s.weights", backup_directory[i], base[i]);
            save_weights(cnn[i], buff);
        }
    }
}

float getSeen(int net){return (float)(*cnn[net]->seen%(largs[net].m))/(float)(largs[net].m);}
void setSeen(int net){*cnn[net]->seen += cnn[net]->batch;}
int maxEpochs(int net){return get_current_batch(cnn[net]) >= cnn[net]->max_batches;}
int getMaxBatches(int net){return cnn[net]->max_batches;};
int getTrainSamples(){return numTrainSamples;}
int getCurrentBatch(int net){return get_current_batch(cnn[net]);};