#include "roadSideExample.h"

// #define TRAINING

int roadSideExample();

void roadSideExample_I_colour(float);
void roadSideExample_I_shape(float);
void roadSideExample_I_content(float);

void roadSideExample_O_message(char **);

int main(void)
{
    #ifdef TRAINING
    srand(time(NULL));
    ANN ann;
    int numlayers = 3;
	int layers[3] = {10,10,5};
	int bias = 1;
	int activation[2] = {0,0};
    ann_init(&ann, numlayers,layers,bias,activation); 
    ann_train_batch(&ann, "basic75data.txt", 1000, 0.01, 1);
    ann_save_to_file(&ann, "TrainedKeyan.net");
    #else
    roadSideExample();
    for(int i = 0; i < 2; i++)
    {
        roadSideExample_I_colour(0.0);
        roadSideExample_I_shape(0.0);
        roadSideExample_I_content(0.0);
        roadSideExample();
    }
    #endif

    return 0;   
}

void roadSideExample_O_message(char ** out)
{
    printf("ANN output: %s\n", out);
}