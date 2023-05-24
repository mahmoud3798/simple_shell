#include "simple_shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

/**
 * execute_command - Execute a command with its arguments.
 * @command: The command to execute.
 */
void execute_command(char *command)
{
	char *args[10];
	char *token = strtok(command, " ");
	int i = 0;
	pid_t pid;

	while (token != NULL && i < 10)
	{
		args[i] = token;
		token = strtok(NULL, " ");
		i++;
	}
	args[i] = NULL;

	pid = fork();
	if (pid == 0)
	{
		if (execvp(args[0], args) == -1)
			perror("Error");
		exit(EXIT_FAILURE);
	}
	else if (pid < 0)
	{
		perror("Fork failed");
		exit(EXIT_FAILURE);
	}
	else
		wait(NULL);
}
