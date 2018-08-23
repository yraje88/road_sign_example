#include "ensemble.h"
#include "ensemble_validate.h"
#include <sys/time.h>
#include <assert.h>

void train_tmr(char *datacfg, char *cfgfile);

int predict_tmr(char *datacfg, char *cfgfile, char *weightfile, char *filename, int full);

void valid_tmr(char *datacfg, char *cfgfile, char *weightfile, int full);

void train_tmr_all(char *datacfg1, char *datacfg2, char *datacfg3, char *cfgfile1, char *cfgfile2, char *cfgfile3);

void valid_all(char *datacfg, char * cfgfile, char * weightfile1, char * weightfile2, char * weightfile3);

void esterel_tmr();

void esterel_validate_tmr();

// Esterel output functions
void ensemble_O_trained(int train);
void ensemble_O_validated(int valid);
void run_tmr(int argc, char **argv);


