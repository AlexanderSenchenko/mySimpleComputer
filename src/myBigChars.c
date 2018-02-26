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

	mt_gotoXY(x1, y1 + y2 - 1);
	bc_printA(BC_ANGLE_RIGHT_UP);

	for (int i = x1 + 1; i <  x1 + x2 - 1; i++) {
		mt_gotoXY(i, y1);
		bc_printA(BC_LINE_VERTICAL);
	}

	mt_gotoXY(x1 + x2 - 1, y1);
	bc_printA(BC_ANGLE_LEFT_DOWN);

	for (int i = y1 + 1; i < y1 + y2 - 1; i++) {
		mt_gotoXY(x1 + x2 - 1, i);
		bc_printA(BC_LINE_HORIZONTAL);
	}

	for (int i = x1 + 1; i <  x1 + x2 - 1; i++) {
		mt_gotoXY(i, y1 + y2 - 1);
		bc_printA(BC_LINE_VERTICAL);
	}

	mt_gotoXY(x1 + x2 - 1, y1 + y2 - 1);
	bc_printA(BC_ANGLE_RIGHT_DOWN);
	printf("\n");
	
	return 0;
}

int bc_printbigchar(int a[2], int x, int y, enum colors f_color, enum colors b_color)
{
	//int x1 = x, y1 = y;

	for (int i = 0; i < 2; i++) {
		mt_gotoXY(x - 4 + i, y);
		printf("Nuber %d: %d", i, a[i]);

		//mt_ssetfgcolor(f_color);
		//mt_ssetbgcolor(b_color);
		//bc_printA(BC_CAGED_CELL);
		//mt_stopcolor();

		int a_buf = a[i];
		//mt_gotoXY(x - 2 + i, y);
		//printf("%d", a_bit);

		for (int j = 0; j < 4; j++) {
			int buf;

			a_buf = a[i] >> (j * 8);
			//mt_gotoXY(x + (i * 4) + j, y);
			//printf("%d", a_bit);

			buf = a_buf & 0b11111111;
			//mt_gotoXY(x + (i * 4) + j, y);
			//printf("%d", buf);

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

	mt_gotoXY(18, 5);
	return 0;
}