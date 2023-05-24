#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "simple_shell.h"
/**
* main - Entry point
* Return: 0
*/
int main(void)
{
	while (1)
	{
		printf("$ ");
		char command[100];

		fgets(command, 100, stdin);

		if (feof(stdin))
			break;

		command[strcspn(command, "\n")] = '\0';
		execute_command(command);
	}
	return (0);
}
