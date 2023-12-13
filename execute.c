#include "shell.h"

/**
 * execute - check user input and execute if applicable
 * @input: the input from the user to be handled
 *
 * Return: Nothing
 */

void execute(const char *input)
{
	pid_t child_pid;

	if (input[0] == 'e' && input[1] == 'x' && input[2] == 'i' &&
		input[3] == 't' && (input[4] == ' ' || input[4] == '\0'))
	{
		exit_shell();
	}

	if (_strcmp(input, "env") == 0)
	{
        print_environment();
        return;
    }

	child_pid = fork();

	if (child_pid == -1)
	{
		output("Forking error.\n");
		_exit(EXIT_FAILURE);
	}
	else if (child_pid == 0)
	{
		execute_child(input);
	}
	else
	{
		wait(NULL);
	}
}

/**
 * exit_shell - exits the shell
 *
 * Return: Nothing
 */

void exit_shell(void)
{
	_exit(EXIT_SUCCESS);
}

/**
 * print_environment - prints the environment variables
 *
 * Return: Nothing
 */

void print_environment()
{
    char **env;

    env = environ;
    while (*env != NULL)
    {
        output(*env);
        output("\n");
        env++;
    }
}

/**
 * execute_child - executes the command in the child process
 * @input: the input from the user to be handled
 *
 * Return: Nothing
 */

void execute_child(const char *input)
{
	char *args[MAX_TOKENS + 1];
	int i;

	tokenize_input(input, args);
	handle_path(args);
	execute_command(args);

	for (i = 0; args[i] != NULL; ++i)
	{
		free(args[i]);
	}

	exit(EXIT_FAILURE);
}

/**
 * execute_command - check user input and execute if applicable
 * @args: the input from the user to be handled
 *
 * Return: Nothing
 */

void execute_command(char **args)
{
	char *program_name;
	char *error_msg;

	/*program_name = get_program_name(args);*/
	program_name = args[0];

	error_msg = ": not found\n";

	if (execve(args[0], args, environ) == -1)
	{
		output(": 1: ");
		output(program_name);
		output(error_msg);
		_exit(EXIT_FAILURE);
	}
}
