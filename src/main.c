#include <stdio.h>
#include <string.h>
#include <math.h>
#include "memory.h"
#include "myTerm.h"
#include "myBigChars.h"
#include "myReadkey.h"
#include <signal.h>
#include <sys/time.h>

#define BOX_ROW_MEMORY 12
#define BOX_COLUMN_MEMORY 61

#define MINI_BOX_ROW 3
#define MINI_BOX_COLUMN 22

int m_printMemory()
{
	bc_box(1, 1, BOX_ROW_MEMORY, BOX_COLUMN_MEMORY);
	mt_printterm();

	return 0;
}

int m_initprintMemory()
{
	sc_memoryInit();
	m_printMemory();

	return 0;
}

int m_printAccumulator()
{
	int accumulator = 9999;

	bc_box(1, BOX_COLUMN_MEMORY + 1, MINI_BOX_ROW, MINI_BOX_COLUMN);
	mt_gotoXY(1, 67);
	printf(" accumulator ");
	mt_gotoXY(2, 70);
	printf("+%d", accumulator);

	return 0;
}

int m_printInstructionCounter()
{
	int instructionCounter = 0;

	bc_box(4, BOX_COLUMN_MEMORY + 1, MINI_BOX_ROW, MINI_BOX_COLUMN);
	mt_gotoXY(4, 63);
	printf(" instructionCounter ");
	mt_gotoXY(5, 70);
	printf("+%.4d", instructionCounter);

	return 0;
}

int m_printOperation()
{
	bc_box(7, BOX_COLUMN_MEMORY + 1, MINI_BOX_ROW, MINI_BOX_COLUMN);
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

	bc_box(10, BOX_COLUMN_MEMORY + 1, MINI_BOX_ROW, MINI_BOX_COLUMN);
	mt_gotoXY(10, 69);
	printf(" Flags ");
	mt_gotoXY(11, 64);
	printf("A-%d B-%d C-%d F-%d G-%d", 
		value_a, value_b, value_c, value_f, value_g);

	return 0;
}

int m_printBoxCase()
{
	int column = 46;
	int row = 10;
	bc_box(BOX_ROW_MEMORY + 1, 1, row, column);
	return 0;
}

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

int x = 0;
int y = 0;
int x_term = 6;
int y_term = 2;

int m_printCaseBigChar(int value, int coord_y)
{
	switch (value) {
		case 0:
			bc_printbigchar(bcint0, BOX_ROW_MEMORY + 2, coord_y, purple, cyan);
			break;
		case 1:
			bc_printbigchar(bcint1, BOX_ROW_MEMORY + 2, coord_y, purple, cyan);
			break;		
		case 2:
			bc_printbigchar(bcint2, BOX_ROW_MEMORY + 2, coord_y, purple, cyan);
			break;
		case 3:
			bc_printbigchar(bcint3, BOX_ROW_MEMORY + 2, coord_y, purple, cyan);
			break;
		case 4:
			bc_printbigchar(bcint4, BOX_ROW_MEMORY + 2, coord_y, purple, cyan);
			break;
		case 5:
			bc_printbigchar(bcint5, BOX_ROW_MEMORY + 2, coord_y, purple, cyan);
			break;
		case 6:
			bc_printbigchar(bcint6, BOX_ROW_MEMORY + 2, coord_y, purple, cyan);
			break;
		case 7:
			bc_printbigchar(bcint7, BOX_ROW_MEMORY + 2, coord_y, purple, cyan);
			break;
		case 8:
			bc_printbigchar(bcint8, BOX_ROW_MEMORY + 2, coord_y, purple, cyan);
			break;
		case 9:
			bc_printbigchar(bcint9, BOX_ROW_MEMORY + 2, coord_y, purple, cyan);
			break;
		case 10:
			bc_printbigchar(bcintA, BOX_ROW_MEMORY + 2, coord_y, purple, cyan);
			break;
		case 11:
			bc_printbigchar(bcintB, BOX_ROW_MEMORY + 2, coord_y, purple, cyan);
			break;
		case 12:
			bc_printbigchar(bcintC, BOX_ROW_MEMORY + 2, coord_y, purple, cyan);
			break;
		case 13:
			bc_printbigchar(bcintD, BOX_ROW_MEMORY + 2, coord_y, purple, cyan);
			break;
		case 14:
			bc_printbigchar(bcintE, BOX_ROW_MEMORY + 2, coord_y, purple, cyan);
			break;
		case 15:
			bc_printbigchar(bcintF, BOX_ROW_MEMORY + 2, coord_y, purple, cyan);
			break;
	}
	return 0;
}

int m_printCase()
{
	bc_printbigchar(bcintp, BOX_ROW_MEMORY + 2, 2, purple, cyan);
	
	int value;
	int rank[4];
	//int mult = 0;
	sc_memoryGet(y * 10 + x, &value);

	/* 10 */
	// for (int i = 38, j = 0; i >= 11; i -= 9, j++) {
	// 	mult = pow(10, j);
	// 	rank = value / mult;
	// 	if (rank > 9) {
	// 		rank %= 10;
	// 	}

	// 	m_printCaseBigChar(rank, i);
	// }

	/* 16 */
	// int i = 38;
	// if (value < 16) {
	// 	m_printCaseBigChar(value, i);
	// } else if (value >= 16) {
	// 	rank = value % 16;
	// 	m_printCaseBigChar(rank, i);
	// 	m_printCaseBigChar(value / 16, i - 9);
	// }

	/* 16(beta) */
	for (int i = 0; i < 4; ++i) {
		rank[i] = value % 16;
		value /= 16;
	}

	for (int i = 38, j = 0; i >= 11; i -= 9, j++) {
		m_printCaseBigChar(rank[j], i);
	}

	return 0;
}

int m_printKeys()
{
	int column = 37;
	int row = 10;

	bc_box(13, 47, row, column);
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
	mt_gotoXY(21, 48);
	printf("q   - exit");
	return 0;
}

int m_printAll()
{
	mt_clrscr();

	//m_printMemory();
	m_initprintMemory();
	m_printAccumulator();
	m_printInstructionCounter();
	m_printOperation();
	m_printFlags();
	m_printBoxCase();
	//m_printCase();
	m_printKeys();

	mt_gotoXY(1, 1);

	fflush(stdout);

	return 0;
}

int m_set_bgcolor(int ind)
{
	if (ind == 1) {
		enum colors a = cyan;
		mt_ssetbgcolor(a);
		mt_gotoXY(y_term, x_term - 4);
		printf("+%.4X", memory[y * 10 + x]);
		mt_stopcolor();
	} else if (ind == 0) {
		mt_stopcolor();
		mt_gotoXY(y_term, x_term - 4);
		printf("+%.4X", memory[y * 10 + x]);
	} else {
		return 1;
	}
	return 0;
}

int reset_bgcolor()
{
	m_set_bgcolor(0);
	m_set_bgcolor(1);
	fflush(stdout);

	return 0;
}

int m_all()
{
	enum keys key;
	//enum keys key_oper;

	m_printAll();

	m_set_bgcolor(1);
	m_printCase();
	fflush(stdout);

	while (key != key_q) {
	//do {
		rk_readkey(&key);

		if (key == key_s) {
			sc_memorySave("Test.bin");
		} else if (key == key_l) {
			sc_memoryLoad("Test.bin");
			m_printMemory();
			mt_gotoXY(23, 1);
			fflush(stdout);
		} else if (key == key_up) {
			if (y != 0) {
				m_set_bgcolor(0);
				y--;
				y_term--;
				m_set_bgcolor(1);
			}
		} else if (key == key_down) {
			if (y != 9) {
				m_set_bgcolor(0);
				y++;
				y_term++;
				m_set_bgcolor(1);
			}
		} else if (key == key_right) {
			m_set_bgcolor(0);
			if (x != 9) {
				x++;
				x_term += 6;		
			} else if (x == 9 && y != 9) {
				x = 0;
				x_term = 6;
				y++;
				y_term++;
			}
			m_set_bgcolor(1);
		} else if (key == key_left) {
			m_set_bgcolor(0);
			if (x != 0) {
				x--;
				x_term -= 6;
			} else if (x == 0 && y != 0) {
				x = 9;
				x_term = 60;
				y--;
				y_term--;
			}
			m_set_bgcolor(1);
		} else if (key >= 0 && key <= 9) {
			//mt_gotoXY(25, 1);
			int value;
			sc_memoryGet(y * 10 + x, &value);
			sc_memorySet(y * 10 + x, key + value);
			m_printMemory();
			fflush(stdout);
		} //else if (key == key_plus || key_minus) {
		// 	key_oper = key;
		// 	m_printCaseOper(key_oper);
		// }

		reset_bgcolor();
		m_printCase();

		mt_gotoXY(23, 1);
		//printf("y = %d x = %d \n", y, x);
		//printf("y_term = %d x_term = %d ", y_term, x_term);
		fflush(stdout);
	//} while (key != key_q);
	}

	mt_gotoXY(26, 1);

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

int test_readkey()
{
	mt_clrscr();
	enum keys key;

	while (key != 0) {
		rk_readkey(&key);
		printf("%d\n", key);
	}
	
	return 0;
}

void sighandler(int signo)
{
	printf("Test");
}

int test_signal1()
{
	int x = 0;

	signal(SIGUSR1, sighandler);
	do {
		printf("Input x = ");
		scanf("%d", &x);
		if (x & 0x0A)
			raise(SIGUSR1);
	} while (x != 99);

	return 0;
}

int test_signal2()
{
	struct itimerval nval, oval;

	signal(SIGALRM, sighandler);

	nval.it_interval.tv_sec = 3;
	nval.it_interval.tv_usec = 500;
	nval.it_value.tv_sec = 1;
	nval.it_value.tv_usec = 0;

	setitimer(ITIMER_REAL, &nval, &oval);

	while (1) {
		pause();
	}

	return 0;
}

int main()
{
	//test_memory();
	//test_term();
	//test_bigchar();
	//test_readkey();
	//test_signal1();
	//test_signal2();
		
	//m_printAll();
	m_all();
	return 0;
}
