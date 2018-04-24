#include "myTerm.h"
#include <stdio.h>

int mt_clrscr()
{
	printf("\E[H\E[J");

	return 0;
}

int mt_gotoXY(int y, int x)
{

	printf("\E[%d;%dH", y, x);

	return 0;
}

int mt_getscreensize(int *rows, int *cols)
{
	struct winsize ws;

	if (ioctl(1, TIOCGWINSZ, &ws)) {
		return 1;
	} else {
		*rows = ws.ws_row;
		*cols = ws.ws_col;
	}

	return 0;
}

int mt_ssetfgcolor(enum colors color)
{
	printf("\E[3%dm", color);

	return 0;
}

int mt_ssetbgcolor(enum colors color)
{
	printf("\E[4%dm", color);

	return 0;
}

int mt_stopcolor()
{
	printf("\E[0m");

	return 0;
}

int mt_printterm()
{
	mt_gotoXY(1, 28);
	printf(" Memory ");
	for (int i = 0; i < 10; i++) {
		mt_gotoXY(2 + i, 2);
		for (int j = 0; j < 10; j++) {
			if (j != 0) {
				printf(" ");
			}
			printf("+%.4X", memory[i * 10 + j]);
		}
		printf("\n");
	}

	return 0;
}
