#include "cpu.h"

int CU()
{
	int value = 0;
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
			case READ:
				mt_gotoXY(24, 14);
				for (int i = 0; i < 70; i++) {
					printf(" ");
				}
				printf("\n");

				mt_gotoXY(24, 15);
				scanf("%d", &value);
				sc_memorySet(operand, value);
				break;
			case WRITE:
				mt_gotoXY(24, 14);
				for (int i = 0; i < 70; i++) {
					printf(" ");
				}
				printf("\n");

				sc_memoryGet(operand, &value);
				mt_gotoXY(24, 15);
				printf("%d\n", value);
				break;
			case LOAD:
				sc_memoryGet(operand, &accumulator);
				break;
			case STORE:
				sc_memorySet(operand, accumulator);
				// accumulator = 0;
				break;
			case JUMP:
				if (operand >= SIZE || operand < 0) {
					sc_regSet(M, 1);
					break;
				}
				instructionCounter = --operand;
				break;
			case JNEG:
				if (accumulator < 0) {
					if (operand >= SIZE || operand < 0) {
						sc_regSet(M, 1);
						break;
					}
					instructionCounter = --operand;
				}
				break;
			case JZ:
				if (accumulator == 0) {
					if (operand >= SIZE || operand < 0) {
						sc_regSet(M, 1);
						break;
					}
					instructionCounter = --operand;
				}
				break;
			case HALT:
				sc_regSet(T, 0);
				return 1;
				break;
			case JNP:
				if ((accumulator % 2) != 0) {
					if (operand >= SIZE || operand < 0) {
						sc_regSet(M, 1);
						break;
					}
					instructionCounter = --operand;
				}
				break;
		}
	}

	if (instructionCounter + 1 < SIZE) {
		instructionCounter++;
	} else {
		sc_regSet(M, 1);
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
