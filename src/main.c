#include <stdio.h>
#include "memory.h"

int main()
{
	int value;
	sc_memoryInit();
	sc_memorySet(4, 24);
	sc_memoryGet(5, &value);
	printf("%d\n", value);

	sc_memoryPrint();

	sc_memorySave("Test.bin");
	//sc_memoryInit();
	//sc_memoryPrint();
	//sc_memoryLoad("Test");
	//sc_memoryPrint();

	sc_regInit();
	sc_regFlagPrint();

	sc_regSet(B, 1);
	sc_regSet(A, 1);
	printf("Flag B and A: "); 
	sc_regFlagPrint();

	
	sc_regGet(B, &value);
	printf("Reg B %d\n", value);

	return 0;
}
