/* sscc : C CODE OF SORTED EQUATIONS ensemble - INLINE MODE */

/* AUXILIARY DECLARATIONS */

#ifndef STRLEN
#define STRLEN 81
#endif
#define _COND(A,B,C) ((A)?(B):(C))
#ifdef TRACE_ACTION
#include <stdio.h>
#endif
#ifndef NULL
#define NULL ((char*)0)
#endif

#ifndef __EXEC_STATUS_H_LOADED
#define __EXEC_STATUS_H_LOADED

typedef struct {
unsigned int start:1;
unsigned int kill:1;
unsigned int active:1;
unsigned int suspended:1;
unsigned int prev_active:1;
unsigned int prev_suspended:1;
unsigned int exec_index;
unsigned int task_exec_index;
void (*pStart)();
void (*pRet)();
} __ExecStatus;

#endif
#define __ResetExecStatus(status) {\
   status.prev_active = status.active; \
   status.prev_suspended = status.suspended; \
   status.start = status.kill = status.active = status.suspended = 0; }
#define __DSZ(V) (--(V)<=0)
#define BASIC_TYPES_DEFINED
typedef int boolean;
typedef int integer;
typedef char* string;
#define _true 1
#define _false 0
#define __ensemble_GENERIC_TEST(TEST) return TEST;
typedef void (*__ensemble_APF)();
static __ensemble_APF *__ensemble_PActionArray;

#include "ensemble.h"

/* EXTERN DECLARATIONS */

#ifndef _NO_EXTERN_DEFINITIONS
#ifndef _NO_FUNCTION_DEFINITIONS
#ifndef _forwardTrainTickCNN_DEFINED
#ifndef forwardTrainTickCNN
extern float forwardTrainTickCNN(integer);
#endif
#endif
#ifndef _inTrainBounds_DEFINED
#ifndef inTrainBounds
extern integer inTrainBounds(integer ,float);
#endif
#endif
#ifndef _getSeen_DEFINED
#ifndef getSeen
extern float getSeen(integer);
#endif
#endif
#ifndef _maxEpochs_DEFINED
#ifndef maxEpochs
extern integer maxEpochs(integer);
#endif
#endif
#ifndef _getTrainSamples_DEFINED
#ifndef getTrainSamples
extern integer getTrainSamples();
#endif
#endif
#endif
#ifndef _NO_PROCEDURE_DEFINITIONS
#ifndef _backwardTrainTickCNN_DEFINED
#ifndef backwardTrainTickCNN
extern void backwardTrainTickCNN(integer);
#endif
#endif
#ifndef _updateTrainTickCNN_DEFINED
#ifndef updateTrainTickCNN
extern void updateTrainTickCNN(integer);
#endif
#endif
#ifndef _forwardValidTickCNN_DEFINED
#ifndef forwardValidTickCNN
extern void forwardValidTickCNN(integer ,integer);
#endif
#endif
#ifndef _tryBackup_DEFINED
#ifndef tryBackup
extern void tryBackup();
#endif
#endif
#ifndef _updateOutput_DEFINED
#ifndef updateOutput
extern void updateOutput(integer);
#endif
#endif
#ifndef _runValidTest_DEFINED
#ifndef runValidTest
extern void runValidTest();
#endif
#endif
#endif
#endif

/* INITIALIZED CONSTANTS */

/* MEMORY ALLOCATION */

static integer __ensemble_V0;
static integer __ensemble_V1;
static float __ensemble_V2;
static integer __ensemble_V3;
static integer __ensemble_V4;


/* INPUT FUNCTIONS */


/* ACTIONS */

/* PREDEFINED ACTIONS */

/* PRESENT SIGNAL TESTS */

/* OUTPUT ACTIONS */

#define __ensemble_A1 \
ensemble_O_trained(__ensemble_V0)
#define __ensemble_A2 \
ensemble_O_validated(__ensemble_V1)

/* ASSIGNMENTS */

#define __ensemble_A3 \
__ensemble_V0 = 0
#define __ensemble_A4 \
__ensemble_V1 = 0
#define __ensemble_A5 \
__ensemble_V3 = 0
#define __ensemble_A6 \
__ensemble_V2 = forwardTrainTickCNN(0)
#define __ensemble_A7 \
__ensemble_V0 = 1
#define __ensemble_A8 \
__ensemble_V4 = 0
#define __ensemble_A9 \
__ensemble_V4 = __ensemble_V0
#define __ensemble_A10 \
__ensemble_V1 = 1
#define __ensemble_A11 \
__ensemble_V3 = __ensemble_V3+1

/* PROCEDURE CALLS */

#define __ensemble_A12 \
backwardTrainTickCNN(0)
#define __ensemble_A13 \
updateTrainTickCNN(0)
#define __ensemble_A14 \
tryBackup()
#define __ensemble_A15 \
forwardValidTickCNN(0,__ensemble_V3)
#define __ensemble_A16 \
updateOutput(__ensemble_V3)
#define __ensemble_A17 \
runValidTest()

/* CONDITIONS */

#define __ensemble_A18 \
maxEpochs(0)==0
#define __ensemble_A19 \
maxEpochs(0)==1
#define __ensemble_A20 \
__ensemble_V4==1
#define __ensemble_A21 \
__ensemble_V3<getTrainSamples()

/* DECREMENTS */

/* START ACTIONS */

/* KILL ACTIONS */

/* SUSPEND ACTIONS */

/* ACTIVATE ACTIONS */

/* WRITE ARGS ACTIONS */

/* RESET ACTIONS */

#define __ensemble_A22 \


/* ACTION SEQUENCES */

/* FUNCTIONS RETURNING NUMBER OF EXEC */

int ensemble_number_of_execs () {
return (0);
}


/* AUTOMATON (STATE ACTION-TREES) */



static void __ensemble__reset_input () {
}

/* REDEFINABLE BIT TYPE */

#ifndef __SSC_BIT_TYPE_DEFINED
typedef char __SSC_BIT_TYPE;
#endif

/* REGISTER VARIABLES */

static __SSC_BIT_TYPE __ensemble_R[2] = {_true,
 _false};

/* AUTOMATON ENGINE */

int ensemble () {
/* AUXILIARY VARIABLES */

static __SSC_BIT_TYPE E[8];
if (__ensemble_R[0]) {
__ensemble_A3;
#ifdef TRACE_ACTION
fprintf(stderr, "__ensemble_A3\n");
#endif
}
E[0] = __ensemble_R[1]&&!(__ensemble_R[0]);
E[1] = E[0]&&(
#ifdef TRACE_ACTION
fprintf(stderr, "test 18\n"),
#endif
__ensemble_A18);
E[2] = E[0]&&!(E[1]);
if (E[2]) {
__ensemble_A7;
#ifdef TRACE_ACTION
fprintf(stderr, "__ensemble_A7\n");
#endif
}
if (E[2]) {
__ensemble_A1;
#ifdef TRACE_ACTION
fprintf(stderr, "__ensemble_A1\n");
#endif
}
if (__ensemble_R[0]) {
__ensemble_A8;
#ifdef TRACE_ACTION
fprintf(stderr, "__ensemble_A8\n");
#endif
}
if (__ensemble_R[0]) {
__ensemble_A22;
#ifdef TRACE_ACTION
fprintf(stderr, "__ensemble_A22\n");
#endif
}
if (__ensemble_R[0]) {
__ensemble_A5;
#ifdef TRACE_ACTION
fprintf(stderr, "__ensemble_A5\n");
#endif
}
if (E[1]) {
__ensemble_A6;
#ifdef TRACE_ACTION
fprintf(stderr, "__ensemble_A6\n");
#endif
}
if (E[1]) {
__ensemble_A12;
#ifdef TRACE_ACTION
fprintf(stderr, "__ensemble_A12\n");
#endif
}
if (E[1]) {
__ensemble_A13;
#ifdef TRACE_ACTION
fprintf(stderr, "__ensemble_A13\n");
#endif
}
if (E[1]) {
__ensemble_A14;
#ifdef TRACE_ACTION
fprintf(stderr, "__ensemble_A14\n");
#endif
}
E[3] = E[0]&&(
#ifdef TRACE_ACTION
fprintf(stderr, "test 19\n"),
#endif
__ensemble_A19);
E[4] = E[3]&&(
#ifdef TRACE_ACTION
fprintf(stderr, "test 20\n"),
#endif
__ensemble_A20);
E[5] = E[4]&&(
#ifdef TRACE_ACTION
fprintf(stderr, "test 21\n"),
#endif
__ensemble_A21);
if (E[5]) {
__ensemble_A15;
#ifdef TRACE_ACTION
fprintf(stderr, "__ensemble_A15\n");
#endif
}
if (E[5]) {
__ensemble_A16;
#ifdef TRACE_ACTION
fprintf(stderr, "__ensemble_A16\n");
#endif
}
E[6] = E[4]&&!(E[5]);
if (E[6]) {
__ensemble_A17;
#ifdef TRACE_ACTION
fprintf(stderr, "__ensemble_A17\n");
#endif
}
if (E[6]) {
__ensemble_A10;
#ifdef TRACE_ACTION
fprintf(stderr, "__ensemble_A10\n");
#endif
}
E[7] = E[5]||E[6];
if (E[7]) {
__ensemble_A11;
#ifdef TRACE_ACTION
fprintf(stderr, "__ensemble_A11\n");
#endif
}
E[4] = E[3]&&!(E[4]);
E[3] = E[0]&&!(E[3]);
__ensemble_R[1] = __ensemble_R[0]||((E[1]||E[2]||E[7]||E[4]||E[3])&&(E[1]||E[2])&&(E[7]||E[4]||E[3]));
E[3] = __ensemble_R[1];
if (E[2]&&E[3]) {
__ensemble_A9;
#ifdef TRACE_ACTION
fprintf(stderr, "__ensemble_A9\n");
#endif
}
if (__ensemble_R[0]) {
__ensemble_A4;
#ifdef TRACE_ACTION
fprintf(stderr, "__ensemble_A4\n");
#endif
}
if (E[6]) {
__ensemble_A2;
#ifdef TRACE_ACTION
fprintf(stderr, "__ensemble_A2\n");
#endif
}
E[4] = !(_true);
__ensemble_R[0] = !(_true);
__ensemble__reset_input();
return E[3];
}

/* AUTOMATON RESET */

int ensemble_reset () {
__ensemble_R[0] = _true;
__ensemble_R[1] = _false;
__ensemble__reset_input();
return 0;
}
