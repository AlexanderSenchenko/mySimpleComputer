#include "cpu.h"

int CU()
{
	int value;
	int command;
	int operand;

	sc_memoryGet(instructionCounter, &value);

	if (sc_commandDecode(value, &command, &operand) == 1) {
		sc_regSet(E, 1);
		sc_regSet(T, 1);
		return 1;
	}

	#if 0
	mt_gotoXY(23, 1);
	printf("Value %d\n", value);
	printf("Command %.2x\n", command);
	printf("Operand %.2x\n", operand);
	#endif

	if (command >= 0x30 && command <= 0x33) {
		ALU(command, operand);
	} else {
		#if 1
		mt_gotoXY(23, 1);
		printf("___________________\n");
		printf("___________________\n");
		printf("___________________\n");
		printf("___________________\n");
		printf("___________________\n");
		#endif
		switch (command)
		{
			case LOAD:
				// mt_gotoXY(23, 1);
				// printf("Command %.2x\n", command);
				// printf("Kek, you are stupid\n");
				accumulator = operand;
				break;
			case STORE:
				// mt_gotoXY(23, 1);
				// printf("Command %.2x\n", command);
				// printf("Kek, you are stupid\n");
				// accumulator = operand;
				break;
		}
	}

	return 0;
}

int ALU(int command, int operand)
{
	switch (command)
	{
		case ADD:
			if (accumulator + operand > 0x7FF){
				sc_regSet(P, 1);
				break;
			}
			accumulator += operand;
			break;
		case SUB:
			if (accumulator - operand < 0) {
				sc_regSet(P, 1);
				break;
			}
			accumulator -= operand;
			break;
		case DIVIDE:
			if (operand == 0) {
				sc_regSet(O, 1);
				break;
			} else if (accumulator / operand < 0) {
				sc_regSet(P, 1);
				break;
			}
			accumulator /= operand;
			break;
		case MUL:
			if (accumulator * operand > 0x7FF) {
				sc_regSet(P, 1);
				break;
			}
			accumulator *= operand;
			break;
	}
	return 0;
}