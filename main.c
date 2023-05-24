#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_COMMAND_LENGTH 100

int main(int argc, char *argv[])
{
	char input[MAX_COMMAND_LENGTH];
	char *args[2];
	int status;

	while (1)
	{
		printf("simple_shell> ");
		if (fgets(input, MAX_COMMAND_LENGTH, stdin) == NULL)
		{
			printf("\n");
			break;
		}
		input[strcspn(input, "\n")] = 0; /* Remove new line character */

		if (strcmp(input, "") == 0) /* Empty command */
			continue;
		args[0] = input;
		args[1] = NULL;

		pid_t pid = fork();

		if (pid == -1) /* Fork error */
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		else if (pid == 0) /* Child process */
		{
			if (execve(args[0], args, environ) == -1)
			{
				perror("execve");
				exit(EXIT_FAILURE);
			}
		}
		else /* Parent process */
		{
			waitpid(pid, &status, 0);
		}
	}
	return (0);
}
