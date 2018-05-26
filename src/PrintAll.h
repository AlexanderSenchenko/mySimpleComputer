#ifndef PRINTALL_H
#define PRINTALL_H

#include <stdio.h>
#include "memory.h"
#include "myTerm.h"
#include "myBigChars.h"
#include "myReadkey.h"
#include "cpu.h"

#define BOX_ROW_MEMORY 12
#define BOX_COLUMN_MEMORY 61

#define MINI_BOX_ROW 3
#define MINI_BOX_COLUMN 22

int x;
int y;

int pa_ProgRun();

int pa_resetTerm(int y, int x, int y_term, int x_term);
int pa_initComp(int *y, int *x, int *y_term, int *x_term);
int pa_printAllBox(int y, int x, int y_term, int x_term);

///////////////////////
int pa_resetBGColor(int y, int x, int y_term, int x_term);
int pa_setBGColor(int ind, int y, int x, int y_term, int x_term);

int pa_printMemory();
int pa_printAccumulator();
int pa_printInstructionCounter();
int pa_printOperation(int y, int x);
int pa_printFlags();
int pa_printCase(int y, int x);
int pa_printCaseBigChar(int value, int coord_y);

///////////////////////
int pa_printBoxMemory();
int pa_printBoxAccumulator();
int pa_printBoxInstructionCounter();
int pa_printBoxOperation();
int pa_printBoxFlags();
int pa_printBoxCase();
int pa_printKeys();

#endif
