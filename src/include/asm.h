#ifndef ASM_H
#define ASM_H

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "memory.h"
#include "cpu.h"

int read_file(char *file_name);
int read_string(char *buf, int len);
int skip_space(char *str, int *lb, int *rb, int len);
int search_space(char *str, char *buf, int *lb, int *rb, int len);
int get_command(char *str, char *buf, int lb, int rb);
int get_number(char *str, char *buf, int lb, int rb);

#endif