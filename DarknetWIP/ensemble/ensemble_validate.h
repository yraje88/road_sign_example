#ifndef ENS_H
#define ENS_H

#include "../darknet/include/darknet.h"

// Forward propagation during validation
void forwardValidTickCNN(int net, int img);

// Esterel output functions
void ensemble_O_validated(int valid);

// Initialisation functions
void destructNets();
void initValidData();
void destructData(); 

// Forward propagation during validation
void forwardValidTickCNN(int net, int img);

// Ensemble functions
void updateOutput(int img);
void runValidTest();

#endif