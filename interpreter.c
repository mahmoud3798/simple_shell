#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "interpreter.h"

#define MAX_ARGS 256

/**
 * get_args - Splits a string into an array of arguments
 * @input: Input string
 *
 * Return: Array of arguments
 */
char **get_args(char *input)
{
	char **args = calloc(MAX_ARGS, sizeof(char *));
	char *arg;
	int i = 0;

	arg = strtok(input, " ");
	while (arg != NULL && i < MAX_ARGS - 1)
	{
		args[i++] = strdup(arg);
		arg = strtok(NULL, " ");
	}
	args[i] = NULL;
	return (args);
}

/**
 * free_args - Frees memory allocated for an array of arguments
 * @args: Array of arguments
 *
 * Return: void
 */
void free_args(char **args)
{
	int i;

	for (i = 0; args[i] != NULL; i++)
		free(args[i]);
	free(args);
}

/**
 * interpret_command - Interprets a command and executes it
 * @input: Input string
 *
 * Return: void
 */
void interpret_command(char *input)
{
	char **args = get_args(input);
	int status;

	if (args[0] == NULL)
	{
		free_args(args);
		return;
	}
	if (strcmp(args[0], "cd") == 0)
	{
		if (args[1] == NULL)
		{
			fprintf(stderr, "cd: expected argument\n");
		}
		else if (chdir(args[1]) != 0)
		{
			perror("cd");
		}
	}
	else
	{
		pid_t pid = fork();

		if (pid == 0)
		{
			execvp(args[0], args);
			fprintf(stderr, "%s: command not found\n", args[0]);
			exit(EXIT_FAILURE);
		}
		else if (pid > 0)
		{
			waitpid(pid, &status, 0);
			free_args(args);
		}
		else
		{
			perror("fork");
		}
	}
}
