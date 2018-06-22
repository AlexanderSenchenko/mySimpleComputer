00 READ 99		; Ввод x
01 READ 98		; Ввод 1 для инкрементирования хз как иначе
02	LOAD 99
03	JZ 12		; Check 0!
04	LOAD 97
05	JZ 14		; Check 97 = 0
06	SUB 98		; Acc--
07	JZ 12		; Check end
08	STORE 97
09	MUL 99
10	STORE 99
11	JUMP 04
12	WRITE 99
13	HALT 00
14	LOAD 99
15	STORE 97
16	JUMP 06		; test