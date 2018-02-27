#include <stdio.h>
#include "memory.h"
#include "myTerm.h"
#include "myBigChars.h"

int main()
{
	/*
	//memory
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
	*/

	/*
	//term
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
	*/

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
	if (isatty(fd)) {
		printf("%s\n", ttyname(fd));
	} else {
		printf("Kek!!!!!\n");
	}
	int count = 0;

	bc_bigcharwrite(fd, a, count);
	//bc_bigcharread(fd, *big, need_count, *count);
	close(fd);

	return 0;
}
