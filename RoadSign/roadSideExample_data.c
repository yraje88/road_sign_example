#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "ann.h"
#include "math.h"
#include "ann.c"
#include "roadSideExample.h"

#define elementCount(a) (sizeof(a)/sizeof(*a))

float ann_weights[2][110] = {
    {-1.281778, -0.550353, 1.035244, 0.949664, -0.560666, 1.259818, -0.119645, -0.754500, -1.108287, 0.712142, -0.503955, 0.307518, 0.655702, 0.727798, 0.384327, 0.300108, -0.225919, 0.372322, -0.261880, 1.273364, -1.739854, 0.889270, 0.897344, 1.108772, 0.738311, 1.107858, -0.640080, -1.010799, -1.299888, 1.289273, -1.246938, 0.060227, 0.521547, 0.864720, 0.091057, 0.549271, -0.384494, 0.002813, -1.186400, 1.102207, 0.787913, -0.985817, 0.973924, -1.215178, -0.509109, -0.549763, 1.115840, 0.596984, -0.111864, -0.603880, 0.546532, -0.066411, -1.243496, 1.102510, 0.297873, -0.968428, 1.403949, 0.711977, -1.400153, 1.252038, 0.372958, 0.734605, 0.914307, 0.600546, 0.507360, 0.401288, 0.825819, 0.884680, 0.713836, 1.035730, -1.272081, 1.219792, -0.145950, 1.460301, 0.980913, -0.243803, -0.439601, 0.095636, -1.871714, 1.176966, 1.250229, 0.798652, -0.689813, -0.968485, 0.558280, -2.273647, 0.948303, 0.786638, 0.062971, -0.388121, 1.075598, 0.627271, -0.946738, 0.073481, 0.860934, -1.441849, 0.774461, 1.020656, -0.536729, 0.089728, 1.589424, 2.573532, 2.874231, 2.030909, 0.545502, 2.568936, 2.870476, 2.529742, 2.266061, 2.423178},
    {-0.687062, -0.247653, -1.102024, -0.422687, 0.150405, -0.291089, -0.356207, -0.492325, 0.145987, -0.187522, -0.361083, -0.349916, -0.235859, -0.301759, -0.408360, -0.421042, -0.985555, -0.053723, -0.417621, -0.395247, 0.498693, -0.432968, -0.195715, -0.026933, 0.217805, -1.229409, -0.347944, -0.630154, -0.679100, -0.855084, -0.101926, -0.249868, -0.031580, -0.025299, -0.691792, -0.119571, -0.650683, 0.157485, -0.804872, -0.646917, -0.347893, -0.673021, -0.857640, -0.566947, 0.298324, 0.192310, -0.621428, -0.924099, 0.148880, 0.079678, -0.539466, -0.848092, 0.016756, -1.161277, -0.566996}
};

// Declare the input and output size
float outputs[5];
float testArray[10] = {0, 0, 0, 0, 0, 0, 0, 0};

int numElements;

ANN ann;

void init()
{
    srand(time(NULL));
    int numlayers = 3;
	int layers[3] = {10,10,5};
	int bias = 1;
	int activation[2] = {0,0};
    ann_init_file(&ann, numlayers,layers,bias,activation,"ANN_weights.txt");  
    // ann_init_custom(&ann, numlayers, layers, 110, ann_weights, bias, activation);
    
    //numElements = sizeof(outputs)/sizeof(*outputs);
}

void outputRoadSign(char ** stringValue, float colour, float shape, float content)
{
    char buffer[elementCount(outputs) * 10];
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

    printf("Inputs: %.0f %.0f %.0f %.0f %.0f %.0f %.0f %.0f %.0f %.0f\n", testArray[0], testArray[1], testArray[2], 
    testArray[3], testArray[4], testArray[5], testArray[6], testArray[7], testArray[8], testArray[9]);

    ann_run(testArray, outputs, &ann);  
   
    for(int i = 0; i < elementCount(outputs); i++)    
    {
        /*
        if(outputs[abc] < 0.5)
            outputs[abc]  = 0;
        else 
            outputs[abc]  = 1;
            */
        sprintf(buffer + i*5, "%.02f ", outputs[i]); 
    }
    strcpy(stringValue, buffer);
}