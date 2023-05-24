#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "interpreter.h"

#define MAX_INPUT_SIZE 1024

/**
 * main - Simple UNIX command line interpreter
 *
 * Return: Always 0.
 */
int main(void)
{
	char input[MAX_INPUT_SIZE];

	while (1)
	{
		printf("$ ");
		if (fgets(input, MAX_INPUT_SIZE, stdin) == NULL)
		{
			printf("\n");
			break;
		}
		input[strcspn(input, "\n")] = '\0';

		if (strcmp(input, "exit") == 0)
		{
			break;
		}
		else
		{
			interpret_command(input);
		}
	}
	return (0);
}
