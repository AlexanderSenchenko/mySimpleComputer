#include "cpu.h"

int CU()
{
	int value;
	int command;
	int operand;

	sc_memoryGet(instructionCounter, &value);

	if (sc_commandDecode(value, &command, &operand)) {
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
		#if 0
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
				sc_memoryGet(operand, &accumulator);
				break;
			case STORE:
				sc_memorySet(operand, accumulator);
				accumulator = 0;
				break;
			case JUMP:
				 instructionCounter = operand - 1;
				break;
			case JNEG:

				break;
			case JZ:
				break;
			case HALT:
				// mt_gotoXY(23, 1);
				// printf("End\n");
				sc_regSet(T, 0);
				return 1;
				break;
		}
	}

	return 0;
}

int ALU(int command, int operand)
{
	int value;
	sc_memoryGet(operand, &value);
	switch (command)
	{
		case ADD:
			if (accumulator + value > 0xFFFF){
				sc_regSet(P, 1);
				break;
			}
			accumulator += value;
			break;
		case SUB:
			if (accumulator - value < -0xFFFE) {
				sc_regSet(P, 1);
				break;
			}
			accumulator -= value;
			break;
		case DIVIDE:
			if (value == 0) {
				sc_regSet(O, 1);
				break;
			} else if (accumulator / value < 0) {
				sc_regSet(P, 1);
				break;
			}
			accumulator /= value;
			break;
		case MUL:
			if (accumulator * value > 0xFFFF) {
				sc_regSet(P, 1);
				break;
			}
			accumulator *= value;
			break;
	}
	return 0;
}
