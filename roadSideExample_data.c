#include<stdio.h>
#include<stdlib.h>
#include "ann.h"
#include "math.h"

// Declare the input and output size
float inputs[3];
float outputs[5];
float testArray[8] = {0, 0, 0, 0, 0, 0, 0, 0};

ANN ann;

void init()
{
    srand(time(NULL));
    int numlayers = 3;
	int layers[3] = {8,8,5};
	int bias = 1;
	int activation[2] = {0, 0};
    ann_init_file(&ann, numlayers,layers,bias,activation,"test.txt");    
}

void outputRoadSign(char ** stringValue, float colour, float shape)
{
    char* outputValue[50];
    for(int ab = 0; ab < 8; ab++)
    {
        testArray[ab] = 0;
    }

    if((int)colour != 5)
        testArray[(int)colour] = 1;

    if((int)shape!= 5)
        testArray[(int)shape+3] = 1;

    ann_run(testArray, outputs, &ann);

}