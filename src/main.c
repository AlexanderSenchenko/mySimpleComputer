#include <stdio.h>
#include "memory.h"

int main()
{
	sc_memoryInit();
	sc_memorySet(4, 24);

	sc_memoryPrint();

	//sc_memorySave("Test.bin");
	//sc_memoryInit();
	//sc_memoryPrint();
	//sc_memoryLoad("Test");
	//sc_memoryPrint();

	sc_regInit();
	sc_regFlagPrint();

	sc_regSet(B, 1);
	sc_regFlagPrint();
	int value;
	sc_regGet(B, &value);
	printf("%d\n", value);

	return 0;
}
