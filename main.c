#include <stdio.h>
#include <stdlib.h>
#include<unistd.h>
#include <string.h>
#include <readline/readline.h>

int main()
{
	char *input;
	char *argv[] = {"ls", NULL, NULL};
	char *clear_argv[] = {"clear", NULL};
	char *echo_argv[] = {"/bin/echo", NULL, NULL};
	char *envp[] = {"TERM=xterm", NULL};
	while (1)
	{
		input = readline("minishell -> ");
		if (strcmp(input, "ls") == 0)
		{
			pid_t pid = fork();
			if (pid == 0)
			{
				execve("/bin/ls", argv, envp);
				exit(1);
			}
			else
                waitpid(pid, NULL, 0);
		}
		else if (strcmp(input, "clear") == 0)
		{
			pid_t pid = fork();
			if (pid == 0)
			{
				execve("/usr/bin/clear", clear_argv, envp);
				exit(1);
			}
			else
                waitpid(pid, NULL, 0);
		}
		else if (strncmp(input, "echo ", 5) == 0)
		{
			if (strncmp(input, "echo -n ", 8) == 0)
				echo_argv[1] = input + 8;
			else
				echo_argv[1] = input + 5;
			pid_t pid = fork();
			if (pid == 0)
			{
				execve("/bin/echo", echo_argv, envp);
				exit(1);
			}
			else
                waitpid(pid, NULL, 0);
		}
		else
			printf("ERROR invalid command\n");
		free(input);
		continue;
	}
}