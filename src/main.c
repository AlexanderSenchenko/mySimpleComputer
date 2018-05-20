#include "PrintAll.h"

#include <signal.h>
#include <sys/time.h>

#include "transGeomAdd.h"

typedef struct {
    uint8_t active;
    uint8_t type;
    tCHS chs_start;
    tLBA l_start;
    tCHS chs_end;
    int32_t ss;
    tLBA end;
} Record;

typedef struct {
    uint8_t full;
    Record records[4];
} Table;

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

	sc_regSet(O, 1);
	sc_regSet(P, 1);
	printf("Flag B and A: "); 
	sc_regFlagPrint();

	
	sc_regGet(O, &value);
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
	instructionCounter = -1;
}

int test_signal()
{
	int x = 0;
	int y = 0;
	int x_term = 6;
	int y_term = 2;

	instructionCounter = 0;

	enum keys key;

	pa_printAll(y, x, y_term, x_term);
	int valueFT;

	while (key != key_q) {
		rk_readkey(&key);

		signal(SIGUSR1, sighandler);

		if (key == key_s) {
			sc_memorySave("Test.bin");
		} else if (key == key_l) {
			sc_memoryLoad("Test.bin");
			pa_printMemory();
			mt_gotoXY(23, 1);
			fflush(stdout);
		} else if (key == key_up) {

			raise(SIGUSR1);

			if (y != 0) {
				pa_setBGColor(0, y, x, y_term, x_term);
				y--;
				y_term--;
				pa_setBGColor(1, y, x, y_term, x_term);
			}
		} else if (key == key_down) {
			if (y != 9) {
				pa_setBGColor(0, y, x, y_term, x_term);
				y++;
				y_term++;
				pa_setBGColor(1, y, x, y_term, x_term);
			}
		} else if (key == key_right) {
			pa_setBGColor(0, y, x, y_term, x_term);
			if (x != 9) {
				x++;
				x_term += 6;		
			} else if (x == 9 && y != 9) {
				x = 0;
				x_term = 6;
				y++;
				y_term++;
			}
			pa_setBGColor(1, y, x, y_term, x_term);
		} else if (key == key_left) {
			pa_setBGColor(0, y, x, y_term, x_term);
			if (x != 0) {
				x--;
				x_term -= 6;
			} else if (x == 0 && y != 0) {
				x = 9;
				x_term = 60;
				y--;
				y_term--;
			}
			pa_setBGColor(1, y, x, y_term, x_term);
		} else if (key >= 0 && key <= 9) {
			int value;
			sc_memoryGet(y * 10 + x, &value);
			sc_memorySet(y * 10 + x, key + value);
		}

		sc_regGet(T, &valueFT);
		if (valueFT == 0) {
			instructionCounter++;
			pa_printInstructionCounter();
		}

		pa_resetBGColor(y, x, y_term, x_term);
		pa_printCase(y, x);

		mt_gotoXY(26, 1);

		fflush(stdout);
	}

	return 0;
}

int test_trans()
{
	tCHS chs;
	tCHS chs_geom;
	tLARGE large;
	tLBA lba;
	// tIDECHS idechs;

	// 15704065 10018890
	lba = 15704065;
	printf("LBA: %d\n", lba);

	g_lba2chs(lba, &chs_geom);
	printf("CHS_GEOM: %d %d %d\n", chs_geom.c, chs_geom.h, chs_geom.s);

	a_lba2chs(chs_geom, lba, &chs);
	printf("CHS: %d %d %d\n", chs.c, chs.h, chs.s);

	// lba = 0;
	// g_chs2lba(chs, &lba);
	// printf("LBA: %d\n", lba);

	lba = 0;
	a_chs2lba(chs_geom, chs, &lba);
	printf("LBA: %d\n", lba);


	printf("LARGE: %d %d %d\n", large.c, large.h, large.s);

	return 0;
}

void smain() {
	tLBA lba = 2046;
	tCHS chs;
	tIDECHS idechs;
	tLARGE large;
	g_lba2chs(lba, &chs);
	printf("CHS: %d/%d/%d\n", chs.c, chs.h, chs.s);
	g_chs2lba(chs, &lba);
	printf("LBA: %d\n", lba);
	lba = 52864;
	g_lba2idechs(lba, &idechs);
	printf("IDECHS: %d/%d/%d\n", idechs.c, idechs.h, idechs.s);
	g_idechs2lba(idechs, &lba);
	printf("LBA: %d\n", lba);
	lba = 52864;
	g_lba2large(lba, &large);
	printf("LARGE: %d/%d/%d\n", large.c, large.h, large.s);
	g_large2lba(large, &lba);
	printf("LBA: %d\n", lba);
}

void nmain() {
	tLBA lba = 900;
	tCHS chs;
	tCHS c_geom;
	c_geom.c = 1024;
	c_geom.h = 16;
	c_geom.s = 63;
	printf("CHS geom: %d/%d/%d\n", c_geom.c, c_geom.h, c_geom.s);
	a_lba2chs(c_geom, lba, &chs);
	printf("CHS: %d/%d/%d\n", chs.c, chs.h, chs.s);

	tLARGE large;
	tLARGE l_geom;
	g_chs2large(c_geom, &l_geom);
	a_lba2large(l_geom, lba, &large);
	printf("LARGE: %d/%d/%d\n", large.c, large.h, large.s);

	tIDECHS idechs;
	tIDECHS idechs_geom;
	g_chs2idechs(c_geom, &idechs_geom);
	a_lba2idechs(idechs_geom, lba, &idechs);
	printf("IDECHS: %d/%d/%d\n", idechs.c, idechs.h, idechs.s);

	tLBA lbachs;
	tLBA lb_g;
	g_chs2lba(c_geom, &lb_g);
	a_chs2lba(c_geom, chs, &lbachs);
	tLBA lbaide;
	a_idechs2lba(idechs_geom, idechs, &lbaide);
	tLBA lbalarge;
	a_large2lba(l_geom, large, &lbalarge);
	printf("%d/%d/%d\n", lbachs, lbaide, lbalarge);
}

int dmain() {
	tIDECHS idechs;
	int hs = 0;
	int ss = 0;
	printf("Enter disk geometry in \"<c> <hs> <ss>\" format: ");
	scanf("%hu%d%d", &idechs.c, &hs, &ss);
	idechs.h = (uint8_t) (hs);
	idechs.s = (uint8_t) (ss);
	int32_t size = ((idechs.c + 1) * (idechs.h + 1) * idechs.s * 512) / (1024 * 1024);
	int32_t free_size = size;
	printf("Size is %d GB\n", size);
	uint8_t was_active = 0;
	tLBA now_at = 1;
	uint32_t table_num = 0;
	Table tables[1024];
	for (uint64_t i = 0; i < 1024; ++i)
	    tables[i].full = 0;

	tLBA l_geom;
	g_idechs2lba(idechs, &l_geom);
	const uint8_t types[10] = {0, 0x1, 0x4, 0x5, 0x6, 0x7, 0xc, 0xd, 0x82, 0x83};
	while (1) {
	    if (tables[table_num].full >= 4)
	        break;

	    int32_t size_to_create = 0;
	    printf("Enter size of the section in GB:\n");
	    scanf("%d", &size_to_create);
	    if (size_to_create == 0)
	        break;

	    if (free_size - size_to_create < 0) {
	        printf("Section is too big.\n");
	        continue;
	    }
	    free_size -= size_to_create;
	    tables[table_num].records[tables[table_num].full].ss = size_to_create * 1024 * 1024 / 512;
	    printf("Choose type:\n1.Empty\n2.FAT12\n3.FAT16<32M\n4.Extended\n5.MS-DOS FAT16\n");
	    printf("6.NTFS\n7.FAT32\n8.FAT16\n9.Linux swap\n10.Linux\n");
	    int32_t type = 0;
	    scanf("%d", &type);
	    while (type < 1 || type > 10) {
	        printf("Come again:\n");
	        scanf("%d", &type);
	    }
	    --type;
	    tables[table_num].records[tables[table_num].full].type = types[type];
	    if (!was_active) {
	        printf("Is active? y/n\n");
	        char c[10];
	        scanf("%10s", c);
	        if (c[0] == 'y') {
	            was_active = 1;
	            tables[table_num].records[tables[table_num].full].active = 1;
	        }
	    }
	    tables[table_num].records[tables[table_num].full].l_start = now_at;
	    tLBA tmp = now_at;
	    now_at = now_at + tables[table_num].records[tables[table_num].full].ss;
	    tables[table_num].records[tables[table_num].full].end = now_at;
	    tCHS chs_geom;
	    g_idechs2chs(idechs, &chs_geom);
	    a_lba2chs(chs_geom, tables[table_num].records[tables[table_num].full].l_start, &tables[table_num].records[tables[table_num].full].chs_start);
	    a_lba2chs(chs_geom, now_at - 1, &tables[table_num].records[tables[table_num].full].chs_end);
	    ++tables[table_num].full;
	    if (type == 3) {
	        now_at = tmp + 2;
	        ++table_num;
	    }
	}
	printf("Active Start           End          ss           Size           Type\n");
	for (uint64_t k = 0; k <= table_num; ++k) {
	    for (uint64_t i = 0; i < tables[k].full; ++i) {
	        if (tables[k].records[i].active == 1) {
	            printf("*      ");
	        } else {
	            printf("       ");
	        }
	        printf("%-15d ", tables[k].records[i].l_start);
	        printf("%-12d ", tables[k].records[i].end);
	        printf("%-17d ", tables[k].records[i].ss);
	        printf("%-14d ", tables[k].records[i].ss * 512);
	        printf("%-4x\n", tables[k].records[i].type);
	    }
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
	// test_signal();

	// test_trans();
	smain();
	printf("\n");
	nmain();
	printf("\n");
	// dmain();

	// pa_ProgRun();
	return 0;
}
