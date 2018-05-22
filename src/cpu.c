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

	#if 1
	mt_gotoXY(23, 1);
	printf("Value %d\n", value);
	printf("Command %.2x\n", command);
	printf("Operand %.2x\n", operand);
	#endif

	if (command >= 0x30 && command <= 0x33) {
		ALU(command, operand);
	} else {
		switch (command)
		{
			case LOAD:
				accumulator = operand;
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
			accumulator += operand;
			break;
		case SUB:
			accumulator -= operand;
			break;
		case DIVIDE:
			accumulator /= operand;
			break;
		case MUL:
			accumulator *= operand;
			break;
	}
	return 0;
}