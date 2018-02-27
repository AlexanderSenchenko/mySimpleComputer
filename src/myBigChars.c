#include <stdio.h>
#include "myBigChars.h"

int bc_printA(char* str)
{
	printf("\E(0%s\E(B", str);
	return 0;
}

int bc_box(int x1, int y1, int x2, int y2)
{
	mt_clrscr();

	mt_gotoXY(x1, y1);
	bc_printA(BC_ANGLE_LEFT_UP);

	for (int i = y1 + 1; i < y1 + y2 - 1; i++) {
		mt_gotoXY(x1, i);
		bc_printA(BC_LINE_HORIZONTAL);
	}

	//mt_gotoXY(x1, y1 + y2 - 1);
	bc_printA(BC_ANGLE_RIGHT_UP);

	for (int i = x1 + 1; i <  x1 + x2 - 1; i++) {
		mt_gotoXY(i, y1);
		bc_printA(BC_LINE_VERTICAL);
	}

	mt_gotoXY(x1 + x2 - 1, y1);
	bc_printA(BC_ANGLE_LEFT_DOWN);

	for (int i = x1 + 1; i <  x1 + x2 - 1; i++) {
		mt_gotoXY(i, y1 + y2 - 1);
		bc_printA(BC_LINE_VERTICAL);
	}

	for (int i = y1 + 1; i < y1 + y2 - 1; i++) {
		mt_gotoXY(x1 + x2 - 1, i);
		bc_printA(BC_LINE_HORIZONTAL);
	}

	//mt_gotoXY(x1 + x2 - 1, y1 + y2 - 1);
	bc_printA(BC_ANGLE_RIGHT_DOWN);
	printf("\n");
	
	return 0;
}

int bc_printbigchar(int a[2], int x, int y, enum colors f_color, enum colors b_color)
{
	for (int i = 0; i < 2; i++) {

		int a_buf = a[i];

		for (int j = 0; j < 4; j++) {
			int buf;

			a_buf = a[i] >> (j * 8);
			buf = a_buf & 0b11111111;

			for (int k = 0; k < 8; k++) {
				int buf_bit = (buf & (0b00000001 << k)) >> k;
				mt_gotoXY(x + (i * 4) + j, y + k);
				//printf("%d\n", buf_bit);
				if (buf_bit != 0) {
					mt_ssetfgcolor(f_color);
					mt_ssetbgcolor(b_color);
					bc_printA(BC_CAGED_CELL);
					mt_stopcolor();
				}
				
			}
		}
	}

	mt_gotoXY(18, 0);
	return 0;
}

int bc_setbigcharpos(int *big, int x, int y, int *value)
{
	return 0;
}

int bc_getbigcharpos(int *big, int x, int y, int *value)
{
	return 0;
}

int bc_bigcharwrite(int fd, int *big, int count)
{
	return 0;
}

int bc_bigcharread(int fd, int *big, int need_count, int *count)
{
	return 0;
}