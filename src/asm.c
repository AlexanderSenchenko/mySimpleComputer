#include "asm.h"

int read_file(char *file_name)
{
	char *buf = NULL;
	size_t len = 0;

	FILE *in = fopen(file_name, "r");
	if(!in) {
		printf("No such file\n");
		return 1;
	}

	sc_memoryInit();

	for (int i = 0; getline(&buf, &len, in) != -1; i++) {
		if (read_string(buf, len, i))
			return 1;
		// printf("\n");
	}

	sc_memorySave("test.o");
	sc_memoryLoad("test.o");

	// sc_memoryInit();

	fclose(in);

	free(buf);

	return 0;
}

int read_string(char *str, int len, int ind)
{
	int value = 0;
	int command, operand = 0;
	int lb = 0, rb = 0;
	char *buf = malloc(sizeof(buf) * len);

	search_space(str, buf, &lb, &rb, len);
	for (int i = lb; i < rb; i++) {
		if (!isdigit(str[i]))
			return 1;
	}
	// printf("%d\n", ind);

	skip_space(str, &lb, &rb, len);



	search_space(str, buf, &lb, &rb, len);
	for (int i = lb; i < rb; i++) {
		if (!isalpha(str[i]) && str[i] != '=')
			return 1;
	}

	if (!(command = get_command(str, buf, lb, rb)))
		return 1;

	skip_space(str, &lb, &rb, len);



	search_space(str, buf, &lb, &rb, len);
	for (int i = lb; i < rb; i++) {
		if (i == lb && str[i] == '+')
			continue;
		if (!isdigit(str[i]))
			return 1;
	}
	operand = get_operand(str, buf, lb, rb);

	skip_space(str, &lb, &rb, len);



	value = (value | command) << 7;
	value |= operand;
	sc_memorySet(ind, value);
	// printf("%X\n", value);

	free(buf);

	return 0;
}

int skip_space(char *str, int *lb, int *rb, int len)
{
	while ((str[*rb] == ' ' || str[*rb] == '\t') && *rb < len)
		(*rb)++;

	*lb = *rb;

	#if 0
	printf("Скип пробела: ");
	printf("%d-", *lb);
	printf("%d ", *rb);

	if (str[*rb] != '\n') {
		printf("%c\n", str[*rb]);
	} else {
		printf("\\n\n");
	}
	
	#endif

	return 0;
}

int search_space(char *str, char *buf, int *lb, int *rb, int len)
{
	while (str[*rb] != ' ' && str[*rb] != '\t' && str[*rb] != '\n' && *rb < len)
		(*rb)++;

	#if 0
	char tmp;

	printf("До пробела: ");
	printf("%d-", *lb);
	printf("%d\n", *rb);

	buf = strcpy(buf, str);

	tmp = buf[*rb];
	buf[*rb] = '\0';

	printf("%s\n", &buf[*lb]);

	buf[*rb] = tmp;
	#endif

	return 0;
}

int get_command(char *str, char *buf, int lb, int rb)
{
	buf = strcpy(buf, str);
	buf[rb] = '\0';

	// printf("%s\n", &buf[lb]);

	if (!strcmp(&buf[lb], "READ"))
		return READ;
	if (!strcmp(&buf[lb], "WRITE"))
		return WRITE;
	if (!strcmp(&buf[lb], "LOAD"))
		return LOAD;
	if (!strcmp(&buf[lb], "STORE"))
		return STORE;
	if (!strcmp(&buf[lb], "ADD"))
		return ADD;
	if (!strcmp(&buf[lb], "SUB"))
		return SUB;
	if (!strcmp(&buf[lb], "DIVIDE"))
		return DIVIDE;
	if (!strcmp(&buf[lb], "MUL"))
		return MUL;
	if (!strcmp(&buf[lb], "JUMP"))
		return JUMP;
	if (!strcmp(&buf[lb], "JNEG"))
		return JNEG;
	if (!strcmp(&buf[lb], "JZ"))
		return JZ;
	// if (strcmp(&buf[lb], "JC"))
	// 	return JC;
	// if (strcmp(&buf[lb], "JB"))
	// 	return JB;
	// if (strcmp(&buf[lb], "SET"))
	// 	return SET;
	if (!strcmp(&buf[lb], "HALT"))
		return HALT;
	if (!strcmp(&buf[lb], "="))
		return 1;

	return 0;
}

int get_operand(char *str, char *buf, int lb, int rb)
{
	buf = strcpy(buf, str);
	buf[rb] = '\0';

	// printf("%s\n", &buf[lb]);

	return atoi(&buf[lb]);
}