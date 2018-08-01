#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "ann.h"
#include "math.h"
#include "ann.c"
#include "roadSideExample.h"

#define elementCount(a) (sizeof(a)/sizeof(*a))

// Declare the input and output size
float inputs[3];
float outputs[5];
float testArray[10] = {0, 0, 0, 0, 0, 0, 0, 0};

int numElements;

ANN ann;

void init()
{
    srand(time(NULL));
    int numlayers = 4;
	int layers[4] = {10,10,5,5};
	int bias = 1;
	int activation[3] = {0,0,0};
    ann_init_file(&ann, numlayers,layers,bias,activation,"test.txt");   
    
    //numElements = sizeof(outputs)/sizeof(*outputs);
}

void outputRoadSign(char ** stringValue, float colour, float shape, float content)
{
    char* outputValue[50];
    sprintf(stringValue, "");
    for(int ab = 0; ab < 8; ab++)
    {
        testArray[ab] = 0;
    }

    /*
    if((int)colour != 5)
        testArray[(int)colour - 1] = 1;

    if((int)shape!= 5)
        testArray[(int)shape+3] = 1;

    if((int)content!= 3)
        testArray[(int)content+8] = 1;
    */


    if((int)colour != 0)
        testArray[(int)colour - 1] = 1;

    if((int)shape!= 0)
        testArray[(int)shape+3] = 1;

    if((int)content!= 0)
        testArray[(int)content+7] = 1;

    ann_run(testArray, outputs, &ann);  
   
    int elements = elementCount(outputs);
    for(int abc = 0; abc < elements; abc++)    
    {
        /*
        if(outputs[abc] < 0.5)
            outputs[abc]  = 0;
        else 
            outputs[abc]  = 1;
            */
        sprintf(outputValue, "%.02f ", outputs[abc]);
    
        strcat(stringValue, outputValue);
    }
    
}