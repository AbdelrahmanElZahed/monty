#include "monty.h"

int main(int argc, char *argv[])
{
	FILE *file;
	char *line = NULL, *opcode, *arg;
	size_t len = 0;
	unsigned int line_number = 0;
	stack_t *stack = NULL;

	if (argc != 2)
	{
		fprintf(stderr, "USAGE: monty file\n");
		exit(EXIT_FAILURE);
	}

	file = fopen(argv[1], "r");
	if (!file)
	{
		fprintf(stderr, "Error: Can't open file %s\n", argv[1]);
		exit(EXIT_FAILURE);
	}

	while (getline(&line, &len, file) != -1)
	{
		line_number++;
		opcode = strtok(line, " \n\t");
		arg = strtok(NULL, " \n\t");

		if (opcode == NULL || opcode[0] == '#') /* Skip empty lines or comments */
			continue;

		if (strcmp(opcode, "push") == 0)
			push(&stack, line_number, arg);
		else if (strcmp(opcode, "pall") == 0)
			pall(&stack);
		else
		{
			fprintf(stderr, "L%d: unknown instruction %s\n", line_number, opcode);
			exit(EXIT_FAILURE);
		}
	}

	free(line);
	fclose(file);
	return (0);
}

