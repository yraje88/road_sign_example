#include "tmr.h"

// Esterel inputs/running functions
int ensemble();

int trained = 0;
int validated = 0;

void train_tmr(char *datacfg, char *cfgfile)
{
    float avg_loss = -1; 
    char *base = basecfg(cfgfile);

    srand(time(0));
    network *net = load_network(cfgfile, NULL, 0);

    int imgs = net->batch * net->subdivisions * 1;

    printf("Learning Rate: %g, Momentum: %g, Decay: %g\n", net->learning_rate, net->momentum, net->decay);
    list *options = read_data_cfg(datacfg);

    char *backup_directory = option_find_str(options, "backup", "/backup/");
    int tag = option_find_int_quiet(options, "tag", 0);
    char *label_list = option_find_str(options, "labels", "data/labels.list");
    char *train_list = option_find_str(options, "train", "data/train.list");
    char *tree = option_find_str(options, "tree", 0);
    if (tree) net->hierarchy = read_tree(tree);
    int classes = option_find_int(options, "classes", 2);

    char **labels = 0;
    if(!tag){
        labels = get_labels(label_list);
    }
    list *plist = get_paths(train_list);
    char **paths = (char **)list_to_array(plist);
    printf("%d\n", plist->size);
    int N = plist->size;
    double time;

    load_args args = {0};
    args.w = net->w;
    args.h = net->h;
    args.threads = 32;
    args.hierarchy = net->hierarchy;

    args.min = net->min_ratio*net->w;
    args.max = net->max_ratio*net->w;
    printf("%d %d\n", args.min, args.max);
    args.angle = net->angle;
    args.aspect = net->aspect;
    args.exposure = net->exposure;
    args.saturation = net->saturation;
    args.hue = net->hue;
    args.size = net->w;

    args.paths = paths;
    args.classes = classes;
    args.n = imgs;
    args.m = N;
    args.labels = labels;
    if (tag){
        args.type = TAG_DATA;
    } else {
        args.type = CLASSIFICATION_DATA;
    }

    data buffer;
    pthread_t load_thread;
    args.d = &buffer;
    load_thread = load_data(args);

    int epoch = (*net->seen)/N;
    while(get_current_batch(net) < net->max_batches || net->max_batches == 0){
        time = what_time_is_it_now();

        pthread_join(load_thread, 0);
        load_thread = load_data(args);

        printf("Loaded: %lf seconds\n", what_time_is_it_now()-time);
        time = what_time_is_it_now();

        float loss = 0;
        loss = train_network(net, *args.d);
        if(avg_loss == -1) avg_loss = loss;
        avg_loss = avg_loss*.9 + loss*.1;
        printf("%ld, %.3f: %f, %f avg, %f rate, %lf seconds, %ld images\n", get_current_batch(net), (float)(*net->seen)/N, loss, avg_loss, get_current_rate(net), what_time_is_it_now()-time, *net->seen);

        if(*net->seen/N > epoch){
            epoch = *net->seen/N;
            char buff[256];
            sprintf(buff, "%s/%s_%d.weights",backup_directory,base, epoch);
            save_weights(net, buff);
        }
        if(get_current_batch(net)%1000 == 0){
            char buff[256];
            sprintf(buff, "%s/%s.backup",backup_directory,base);
            save_weights(net, buff);
        }
    }
    char buff[256];
    sprintf(buff, "%s/%s.weights", backup_directory, base);
    save_weights(net, buff);
    pthread_join(load_thread, 0);

    free_network(net);
    if(labels) free_ptrs((void**)labels, classes);
    free_ptrs((void**)paths, plist->size);
    free_list(plist);
    free(base);
}

int predict_tmr(char *datacfg, char *cfgfile, char *weightfile, char *filename, int full)
{
    int top = 0;
    if(full) printf("======= Starting prediction process =======\n\n");
    else printf("Predicting...\n    ");
    network *net = load_network(cfgfile, weightfile, 0);
    set_batch_network(net, 1);
    srand(2222222);

    list *options = read_data_cfg(datacfg);

    char *name_list = option_find_str(options, "names", 0);
    if(!name_list) name_list = option_find_str(options, "labels", "data/labels.list");
    if(top == 0) top = option_find_int(options, "top", 1);

    int i = 0;
    char **names = get_labels(name_list);
    clock_t time;
    int *indexes = calloc(top, sizeof(int));
    char buff[256];
    char *input = buff;
    while(1){
        if(filename){
            strncpy(input, filename, 256);
        }else{
            printf("Enter Image Path: ");
            fflush(stdout);
            input = fgets(input, 256, stdin);
            if(!input) return -1;
            strtok(input, "\n");
        }
        image im = load_image_color(input, 0, 0);
        image r = letterbox_image(im, net->w, net->h);
        //image r = resize_min(im, 320);
        //printf("%d %d\n", r.w, r.h);
        //resize_network(net, r.w, r.h);
        //printf("%d %d\n", r.w, r.h);

        float *X = r.data;
        time=clock();
        float *predictions = network_predict(net, X);
        if(net->hierarchy) hierarchy_predictions(predictions, net->outputs, net->hierarchy, 1, 1);
        top_k(predictions, net->outputs, top, indexes);
        if(full) fprintf(stderr, "%s: Predicted in %f seconds.\n", input, sec(clock()-time));
        for(i = 0; i < top; ++i){
            int index = indexes[i];
            //if(net->hierarchy) printf("%d, %s: %f, parent: %s \n",index, names[index], predictions[index], (net->hierarchy->parent[index] >= 0) ? names[net->hierarchy->parent[index]] : "Root");
            //else printf("%s: %f\n",names[index], predictions[index]);
            if(full || i == 0) printf("%5.2f%%: %s\n", predictions[index]*100, names[index]);
        }
        if(r.data != im.data) free_image(r);
        free_image(im);
        if (filename) break;
    }
    if(full) printf("\n======= Ending prediction process =======\n");
    else printf("...done!\n");
    free_network(net);

    return indexes[0];
}

void valid_tmr(char *datacfg, char *cfgfile, char *weightfile, int full)
{
    int i, j;
    network *net = load_network(cfgfile, weightfile, 0);
    set_batch_network(net, 1);
    srand(time(0));

    list *options = read_data_cfg(datacfg);

    char *label_list = option_find_str(options, "labels", "data/labels.list");
    char *valid_list = option_find_str(options, "valid", "data/train.list");
    int classes = option_find_int(options, "classes", 2);
    int topk = option_find_int(options, "top", 1);

    char **labels = get_labels(label_list);
    list *plist = get_paths(valid_list);

    char **paths = (char **)list_to_array(plist);
    int m = plist->size;
    free_list(plist);

    float avg_acc = 0;
    float avg_topk = 0;
    int *indexes = calloc(topk, sizeof(int));

    for(i = 0; i < m; ++i){
        int class = -1;
        char *path = paths[i];
        for(j = 0; j < classes; ++j){
            if(strstr(path, labels[j])){
                class = j;
                break;
            }
        }

        image im = load_image_stb(paths[i], 3);
        // image resized = resize_min(im, size);
        // resize_network(net, resized.w, resized.h);

        //show_image(im, "orig");
        //show_image(crop, "cropped");
        //cvWaitKey(0);
        float *pred = network_predict(net, im.data);
        if(net->hierarchy) hierarchy_predictions(pred, net->outputs, net->hierarchy, 1, 1);

        free_image(im);
        // free_image(resized);
        // printf("Here\n");
        top_k(pred, classes, topk, indexes);

        if(indexes[0] == class) avg_acc += 1;
        for(j = 0; j < topk; ++j){
            if(indexes[j] == class) avg_topk += 1;
        }

        if(full || i == m - 1)
            printf("%d: top 1: %f, top %d: %f\n", i, avg_acc/(i+1), topk, avg_topk/(i+1));
    }
    free_network(net);
}

void train_tmr_all(char *datacfg1, char *datacfg2, char *datacfg3, char *cfgfile1, char *cfgfile2, char *cfgfile3)
{
    train_tmr(datacfg1, cfgfile1);
}

void valid_all(char *datacfg, char * cfgfile, char * weightfile1, char * weightfile2, char * weightfile3)
{
    valid_tmr(datacfg, cfgfile, weightfile1, 0);
}

void esterel_tmr()
{
    initNets();
    initTrainData();

    printf("<================ Epochs to train: %d ================>\n\n", getMaxBatches(0));
    double time = what_time_is_it_now();

    int batches = 0;
    ensemble();
    while(!trained)
    {
        printf("Training... EPOCH: %d; %f seconds\n", batches, what_time_is_it_now() - time);
        ensemble();
        batches++;
    }

    printf("\n<=============== Training complete in %f seconds =================>\n", what_time_is_it_now() - time);
    time = what_time_is_it_now();

    initValidData();

    printf("\n<================ Images to validate: %d ================>\n\n", getTrainSamples());
    while(!validated)
    {
        ensemble();
        batches++;
    }
    printf("\n<=============== Validation complete in %f seconds =================>\n", what_time_is_it_now() - time);

    destructNets();
    destructData();
}

// Esterel functions
void ensemble_O_trained(int train)
{
    trained = train;
}
void ensemble_O_validated(int valid)
{
    validated = valid;
}

void run_tmr(int argc, char **argv)
{
    // char *tmr_data = "cfg/tmr/tmr.data";
    char *tmr_data1 = "data/tmr1.data";
    char *tmr_data2 = "data/tmr2.data";
    char *tmr_data3 = "data/tmr3.data";

    // char *tmr_cfg = "cfg/tmr/tmr.cfg";
    char *tmr_cfg1 = "data/tmr1.cfg";
    char *tmr_cfg2 = "data/tmr2.cfg";
    char *tmr_cfg3 = "data/tmr3.cfg";

    // char *tmr_weights = "backup/tmr/tmr.weights";
    char *tmr_weights1 = "backup/tmr1.weights";
    char *tmr_weights2 = "backup/tmr2.weights";
    char *tmr_weights3 = "backup/tmr3.weights";

    char *filename = (argc > 3) ? argv[3]: 0;
    if(0==strcmp(argv[1], "predict")) predict_tmr(tmr_data1, tmr_cfg1, tmr_weights1, filename, 1);
    else if(0==strcmp(argv[1], "train")) train_tmr(tmr_data1, tmr_cfg1);
    else if(0==strcmp(argv[1], "valid")) valid_tmr(tmr_data1, tmr_cfg1, tmr_weights1, 1);
    else if(0==strcmp(argv[1], "validall")) valid_all(tmr_data1, tmr_cfg1, tmr_weights1, tmr_weights2, tmr_weights3);
    else if(0==strcmp(argv[1], "trainall")) train_tmr_all(tmr_data1, tmr_data2, tmr_data3, tmr_cfg1, tmr_cfg2, tmr_cfg3); 
    else if(0==strcmp(argv[1], "esterel")) esterel_tmr();
}


