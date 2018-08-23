#ifndef ENS_H
#define ENS_H

#include "../darknet/include/darknet.h"

#define NUM_CLASSES             6
#define TOPK                    2
#define NUM_NETS                1

// Esterel output functions
void ensemble_O_trained(int train);
void ensemble_O_validated(int valid);

// Initialisation functions
void initNets();
void destructNets();
void initTrainData();
void initValidData();
void destructData(); 

// Forward propagation during training
float forwardTrainTickCNN(int net);
// Back-propagation during training
void backwardTrainTickCNN(int net);
// Update network after back-propagation
void updateTrainTickCNN(int net);

// Forward propagation during validation
void forwardValidTickCNN(int net, int img);

// Ensemble functions
void updateOutput(int img);
void runValidTest();

float getLoss();

// Helper functions
void tryBackup();
int inTrainBounds(int net, float seen);
float getSeen(int net);
void setSeen(int net);
int maxEpochs(int net);
int getTrainSamples();
int getMaxBatches(int net);
int getCurrentBatch(int net);

#endif