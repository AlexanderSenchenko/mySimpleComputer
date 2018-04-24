#include "PrintAll.h"

#include <signal.h>
#include <sys/time.h>

/* Test lab */
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
/* */

int main()
{
	// test_memory();
	// test_term();
	// test_bigchar();
	// test_readkey();
	// test_signal1();
	// test_signal2();

	pa_ProgRun();
	return 0;
}
