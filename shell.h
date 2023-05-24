#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define BUFFER_SIZE 1024

ssize_t read_command(char **buffer, size_t *bufsize);
int parse_command(char *buffer, char **args);
void execute_command(char **args);

#endif /* SHELL_H */
