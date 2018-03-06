#include <stdio.h>
#include "memory.h"
#include "myTerm.h"
#include "myBigChars.h"

#define BOX_ROW_MEMORY 12
#define BOX_COLUMN_MEMORY 61

#define MINI_BOX_ROW 3
#define MINI_BOX_COLUMN 22

int m_printMemory()
{
	sc_memoryInit();
	bc_box(1, 1, BOX_ROW_MEMORY, BOX_COLUMN_MEMORY);//box memory
	mt_printterm();

	return 0;
}

int m_printAccumulator()
{
	int accumulator = 9999;

	bc_box(1, BOX_COLUMN_MEMORY + 1, MINI_BOX_ROW, MINI_BOX_COLUMN);//box accumulator
	mt_gotoXY(1, 67);
	printf(" accumulator ");
	mt_gotoXY(2, 70);
	printf("+%d", accumulator);

	return 0;
}

int m_printInstructionCounter()
{
	int instructionCounter = 0;

	bc_box(4, BOX_COLUMN_MEMORY + 1, MINI_BOX_ROW, MINI_BOX_COLUMN);//box instructionCounter
	mt_gotoXY(4, 63);
	printf(" instructionCounter ");
	mt_gotoXY(5, 70);
	printf("+%.4d", instructionCounter);

	return 0;
}

int m_printOperation()
{
	bc_box(7, BOX_COLUMN_MEMORY + 1, MINI_BOX_ROW, MINI_BOX_COLUMN);//box operation
	mt_gotoXY(7, 68);
	printf(" Operation ");
	mt_gotoXY(8, 69);
	printf("+00 : 00");

	return 0;
}

int m_printFlags()
{
	int value_a, value_b, value_c, value_f, value_g;

	sc_regGet(A, &value_a);
	sc_regGet(B, &value_b);
	sc_regGet(C, &value_c);
	sc_regGet(F, &value_f);
	sc_regGet(G, &value_g);

	bc_box(10, BOX_COLUMN_MEMORY + 1, MINI_BOX_ROW, MINI_BOX_COLUMN);//box flags
	mt_gotoXY(10, 69);
	printf(" Flags ");
	mt_gotoXY(11, 64);
	printf("A-%d B-%d C-%d F-%d G-%d", 
		value_a, value_b, value_c, value_f, value_g);

	return 0;
}

int m_printCase()
{
	int column = 46;
	int row = 10;
	int bcint9 [2] = {2087074816, 3956832};
	int bcintp [2] = {2115508224, 1579134};

	bc_box(BOX_ROW_MEMORY + 1, 1, row, column);//box case

	bc_printbigchar(bcintp, BOX_ROW_MEMORY + 2, 2, purple, cyan);
	bc_printbigchar(bcint9, BOX_ROW_MEMORY + 2, 11, purple, cyan);
	bc_printbigchar(bcint9, BOX_ROW_MEMORY + 2, 20, purple, cyan);
	bc_printbigchar(bcint9, BOX_ROW_MEMORY + 2, 29, purple, cyan);
	bc_printbigchar(bcint9, BOX_ROW_MEMORY + 2, 38, purple, cyan);

	return 0;
}

int m_printKeys()
{
	int column = 37;
	int row = 10;

	bc_box(13, 47, row, column);//box keys
	mt_gotoXY(13, 48);
	printf(" Keys: ");
	mt_gotoXY(14, 48);
	printf("l   - load");
	mt_gotoXY(15, 48);
	printf("s   - save");
	mt_gotoXY(16, 48);
	printf("r   - run");
	mt_gotoXY(17, 48);
	printf("t   - step");
	mt_gotoXY(18, 48);
	printf("i   - reset");
	mt_gotoXY(19, 48);
	printf("F5  - accumulator");
	mt_gotoXY(20, 48);
	printf("F6  - instructionCounter");
	return 0;
}

int m_printAll()
{
	mt_clrscr();

	m_printMemory();
	m_printAccumulator();
	m_printInstructionCounter();
	m_printOperation();
	m_printFlags();
	m_printCase();
	m_printKeys();

	mt_gotoXY(23, 1);

	return 0;
}

int test_memory()
{
	int value;
	sc_memoryInit();
	sc_memorySet(4, 24);
	sc_memoryGet(5, &value);
	printf("%d\n", value);

	sc_memorySave("Test.bin");
	//sc_memoryLoad("Test");

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

int test_term()
{
	mt_clrscr();

	mt_gotoXY(10, 10);


	int *r = malloc(sizeof(int));
	int *c = malloc(sizeof(int));

	mt_getscreensize(r, c);
	printf("row = %d\tcol = %d\n", *r, *c);

	enum colors f = cyan;
	mt_ssetfgcolor(f);

	enum colors a = white;
	mt_ssetbgcolor(a);

	printf("Test\n");

	mt_stopcolor();

	return 0;
}

int test_bigchar()
{
	mt_clrscr();
	int a[2] = {1010315264, 3158064};
	int value;
	
	bc_box(10, 5, 8, 8);
	bc_printbigchar(a, 10, 5, purple, cyan);

	bc_setbigcharpos(a, 1, 4, 0);
	bc_setbigcharpos(a, 1, 3, 1);
	bc_printbigchar(a, 10, 15, purple, cyan);

	bc_getbigcharpos(a, 1, 4, &value);
	printf("Value = %d\n", value);

	
	int fd = open("BigChar.txt", O_WRONLY);
	int count = 0;

	int *big = malloc(sizeof(int) * 1);
	big[0] = 0;
	big[1] = 0;

	bc_bigcharwrite(fd, a, 1);
	close(fd);

	fd = open("BigChar.txt", O_RDONLY);
	bc_bigcharread(fd, big, 1, &count);
	printf("%d\n", big[0]);
	printf("%d\n", big[1]);
	printf("%d\n", count);
	close(fd);

	free(big);

	return 0;
}

int main()
{
	//test_memory();
	//test_term();
	test_bigchar();
	//m_printAll();

	return 0;
}
