#ifndef PRINTALL_H
#define PRINTALL_H

// #include <stdio.h>
// #include "memory.h"
// #include "myTerm.h"
// #include "myBigChars.h"
// #include "myReadkey.h"

#define BOX_ROW_MEMORY 12
#define BOX_COLUMN_MEMORY 61

#define MINI_BOX_ROW 3
#define MINI_BOX_COLUMN 22

int x = 0;
int y = 0;
int x_term = 6;
int y_term = 2;

int bcint0 [2] = {1717992960, 8283750};
int bcint1 [2] = {471341056, 3938328};
int bcint2 [2] = {538983424, 3935292};
int bcint3 [2] = {2120252928, 8282238};
int bcint4 [2] = {2120640000, 6316158};
int bcint5 [2] = {2114092544, 8273984};
int bcint6 [2] = {33701376, 4071998};
int bcint7 [2] = {811630080, 396312};
int bcint8 [2] = {2120646144, 8283750};
int bcint9 [2] = {2087074816, 3956832};
int bcintA [2] = {2118269952, 4342338};
int bcintB [2] = {1044528640, 4080194};
int bcintC [2] = {37895168, 3949058};
int bcintD [2] = {1111637504, 4080194};
int bcintE [2] = {2114092544, 8258050};
int bcintF [2] = {33717760, 131646};
int bcintp [2] = {2115508224, 1579134};

int pa_all();
int pa_setBGColor(int ind);
int pa_resetBGColor();
int pa_printAll();
int pa_initprintMemory();
int pa_printMemory();
int pa_printAccumulator();
int pa_printInstructionCounter();
int pa_printOperation();
int pa_printFlags();
int pa_printBoxCase();
int pa_printCase();
int pa_printCaseBigChar(int value, int coord_y);
int pa_printKeys();

#endif