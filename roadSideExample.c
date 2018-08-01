/* sscc : C CODE OF SORTED EQUATIONS roadSideExample - INLINE MODE */

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
#define __roadSideExample_GENERIC_TEST(TEST) return TEST;
typedef void (*__roadSideExample_APF)();
static __roadSideExample_APF *__roadSideExample_PActionArray;

#include "roadSideExample.h"

/* EXTERN DECLARATIONS */

#ifndef _NO_EXTERN_DEFINITIONS
#ifndef _NO_PROCEDURE_DEFINITIONS
#ifndef _outputRoadSign_DEFINED
#ifndef outputRoadSign
extern void outputRoadSign(string* ,float ,float ,float);
#endif
#endif
#ifndef _init_DEFINED
#ifndef init
extern void init();
#endif
#endif
#endif
#endif

/* INITIALIZED CONSTANTS */

/* MEMORY ALLOCATION */

static float __roadSideExample_V0;
static boolean __roadSideExample_V1;
static float __roadSideExample_V2;
static boolean __roadSideExample_V3;
static float __roadSideExample_V4;
static boolean __roadSideExample_V5;
static char __roadSideExample_V6[STRLEN];
static integer __roadSideExample_V7;
static char __roadSideExample_V8[STRLEN];


/* INPUT FUNCTIONS */

void roadSideExample_I_colour (float __V) {
__roadSideExample_V0 = __V;
__roadSideExample_V1 = _true;
}
void roadSideExample_I_shape (float __V) {
__roadSideExample_V2 = __V;
__roadSideExample_V3 = _true;
}
void roadSideExample_I_content (float __V) {
__roadSideExample_V4 = __V;
__roadSideExample_V5 = _true;
}

/* ACTIONS */

/* PREDEFINED ACTIONS */

/* PRESENT SIGNAL TESTS */

#define __roadSideExample_A1 \
__roadSideExample_V1
#define __roadSideExample_A2 \
__roadSideExample_V3
#define __roadSideExample_A3 \
__roadSideExample_V5

/* OUTPUT ACTIONS */

#define __roadSideExample_A4 \
roadSideExample_O_message(__roadSideExample_V6)

/* ASSIGNMENTS */

#define __roadSideExample_A5 \
__roadSideExample_V1 = _false
#define __roadSideExample_A6 \
__roadSideExample_V3 = _false
#define __roadSideExample_A7 \
__roadSideExample_V5 = _false
#define __roadSideExample_A8 \
__roadSideExample_V7 = 0
#define __roadSideExample_A9 \
__roadSideExample_V7 = 1
#define __roadSideExample_A10 \
strcpy(__roadSideExample_V6,__roadSideExample_V8)

/* PROCEDURE CALLS */

#define __roadSideExample_A11 \
init()
#define __roadSideExample_A12 \
outputRoadSign(&__roadSideExample_V8,__roadSideExample_V0,__roadSideExample_V2,__roadSideExample_V4)

/* CONDITIONS */

#define __roadSideExample_A13 \
__roadSideExample_V7==0

/* DECREMENTS */

/* START ACTIONS */

/* KILL ACTIONS */

/* SUSPEND ACTIONS */

/* ACTIVATE ACTIONS */

/* WRITE ARGS ACTIONS */

/* RESET ACTIONS */

#define __roadSideExample_A14 \

#define __roadSideExample_A15 \

#define __roadSideExample_A16 \

#define __roadSideExample_A17 \

#define __roadSideExample_A18 \


/* ACTION SEQUENCES */

/* FUNCTIONS RETURNING NUMBER OF EXEC */

int roadSideExample_number_of_execs () {
return (0);
}


/* AUTOMATON (STATE ACTION-TREES) */



static void __roadSideExample__reset_input () {
__roadSideExample_V1 = _false;
__roadSideExample_V3 = _false;
__roadSideExample_V5 = _false;
}

/* REDEFINABLE BIT TYPE */

#ifndef __SSC_BIT_TYPE_DEFINED
typedef char __SSC_BIT_TYPE;
#endif

/* REGISTER VARIABLES */

static __SSC_BIT_TYPE __roadSideExample_R[2] = {_true,
 _false};

/* AUTOMATON ENGINE */

int roadSideExample () {
/* AUXILIARY VARIABLES */

static __SSC_BIT_TYPE E[7];
E[0] = __roadSideExample_R[0]&&!((
#ifdef TRACE_ACTION
fprintf(stderr, "test 1\n"),
#endif
__roadSideExample_A1));
if (E[0]) {
__roadSideExample_A14;
#ifdef TRACE_ACTION
fprintf(stderr, "__roadSideExample_A14\n");
#endif
}
E[1] = __roadSideExample_R[0]&&!((
#ifdef TRACE_ACTION
fprintf(stderr, "test 2\n"),
#endif
__roadSideExample_A2));
if (E[1]) {
__roadSideExample_A15;
#ifdef TRACE_ACTION
fprintf(stderr, "__roadSideExample_A15\n");
#endif
}
E[2] = __roadSideExample_R[0]&&!((
#ifdef TRACE_ACTION
fprintf(stderr, "test 3\n"),
#endif
__roadSideExample_A3));
if (E[2]) {
__roadSideExample_A16;
#ifdef TRACE_ACTION
fprintf(stderr, "__roadSideExample_A16\n");
#endif
}
if (__roadSideExample_R[0]) {
__roadSideExample_A17;
#ifdef TRACE_ACTION
fprintf(stderr, "__roadSideExample_A17\n");
#endif
}
E[3] = __roadSideExample_R[1]&&!(__roadSideExample_R[0]);
E[4] = E[3]&&(
#ifdef TRACE_ACTION
fprintf(stderr, "test 13\n"),
#endif
__roadSideExample_A13);
E[3] = E[3]&&!(E[4]);
if (E[3]) {
__roadSideExample_A12;
#ifdef TRACE_ACTION
fprintf(stderr, "__roadSideExample_A12\n");
#endif
}
if (E[3]) {
__roadSideExample_A10;
#ifdef TRACE_ACTION
fprintf(stderr, "__roadSideExample_A10\n");
#endif
}
if (E[3]) {
__roadSideExample_A4;
#ifdef TRACE_ACTION
fprintf(stderr, "__roadSideExample_A4\n");
#endif
}
E[5] = !(_true);
if (__roadSideExample_R[0]) {
__roadSideExample_A8;
#ifdef TRACE_ACTION
fprintf(stderr, "__roadSideExample_A8\n");
#endif
}
if (__roadSideExample_R[0]) {
__roadSideExample_A18;
#ifdef TRACE_ACTION
fprintf(stderr, "__roadSideExample_A18\n");
#endif
}
if (E[4]) {
__roadSideExample_A11;
#ifdef TRACE_ACTION
fprintf(stderr, "__roadSideExample_A11\n");
#endif
}
if (E[4]) {
__roadSideExample_A9;
#ifdef TRACE_ACTION
fprintf(stderr, "__roadSideExample_A9\n");
#endif
}
__roadSideExample_R[1] = __roadSideExample_R[0]||E[4]||E[3];
E[6] = __roadSideExample_R[1];
__roadSideExample_R[0] = !(_true);
__roadSideExample__reset_input();
return E[6];
}

/* AUTOMATON RESET */

int roadSideExample_reset () {
__roadSideExample_R[0] = _true;
__roadSideExample_R[1] = _false;
__roadSideExample__reset_input();
return 0;
}
