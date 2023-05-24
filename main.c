#include "shell.h"

/**
 * read_command - reads a command from stdin
 * @buffer: pointer to buffer to store command
 * @bufsize: size of buffer
 * Return: number of characters read, or -1 on failure
 **/
ssize_t read_command(char **buffer, size_t *bufsize)
{
	printf("$ ");
	return (getline(buffer, bufsize, stdin));
}

/**
 * parse_command - parses a command into arguments
 * @buffer: command to parse
 * @args: pointer to array to store arguments
 * Return: number of arguments
 **/
int parse_command(char *buffer, char **args)
{
	char *token;
	int i = 0;

	token = strtok(buffer, " \n");
	while (token != NULL)
	{
		args[i++] = token;
		token = strtok(NULL, " \n");
	}
	args[i] = NULL;
	return (i);
}

/**
 * execute_command - executes a command in a child process
 * @args: arguments for command
 * @env: environment variables
 **/
void execute_command(char **args, char *env[])
{
	execvp(args[0], args, env);
	printf("%s: command not found\n", args[0]);
	exit(1);
}
/**
* main - Entry point
* @argc: int
* @argv: char pointer
* @env: environment variables
* Return: always 0
*/
int main(int argc, char *argv[], char *env[])
{
	char *buffer;
	size_t bufsize = BUFFER_SIZE;
	pid_t pid;
	int status;

	buffer = (char *)malloc(bufsize * sizeof(char));
	if (buffer == NULL)
	{
		perror("Unable to allocate buffer");
		exit(1);
	}
	while (1)
	{
		ssize_t nread = read_command(&buffer, &bufsize);

		if (feof(stdin))
		{
			printf("\n");
			exit(0);
		}
		if (nread > 1)
		{
			/* Parse the command and arguments*/
			char *args[10];
			int argc = parse_command(buffer, args);

			/*Fork a child process and execute the command*/
			pid = fork();
			if (pid == 0)
			{
				execute_command(args, env);
			}
			else
			{
				waitpid(pid, &status, 0);
			}
		}
	}
	free(buffer);
	return (0);
}
