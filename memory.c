#include "memory.h"
#include <stdio.h>

int sc_memoryInit()
{
	for (int i = 0; i < SIZE; i++) {
		memory[i] = 0;
	}
	return 0;
}

int sc_memorySet(int address, int value)
{
	if (address >= SIZE || address < 0)
		return 1;//выход за границы памяти

	memory[address] = value;
	
	return 0;
}

int sc_memoryGet(int address, int *value)
{
	if (address >= SIZE || address < 0)
		return 1;//выход за границы памяти (C)

	*value = memory[address];

	return 0;
}

int sc_memorySave(char *filename)
{
	FILE *mem_file = fopen(filename, "wb");

	fwrite(memory, sizeof(int), SIZE, mem_file);
	fclose(mem_file);

	return 0;
}

int sc_memoryLoad(char *filename)
{
	FILE *mem_file = fopen(filename, "rb");

	fread(memory, sizeof(int), SIZE, mem_file);
	fclose(mem_file);

	return 0;
}

int sc_regInit()
{
	registr = 0;
	return 0;
}

int sc_regSet(int value)
{
	registr = registr | value;
	return 0;
}

int sc_regGet(int *value)
{

}

int sc_memoryPrint()
{
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			printf("%.4d\t", memory[i * 10 + j]);
		}
		printf("\n");
	}
	return 0;
}