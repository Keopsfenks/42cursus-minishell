#include <stdio.h>
#include <stdlib.h>
#include<unistd.h>
#include <string.h>
#include"./libft/libft.h"
#include <readline/readline.h>

int	find_env_dir(char **envp, char *find)
{
	int j;

	j = 0;
	while (envp[j])
	{
		if (ft_strncmp(envp[j], find, ft_strlen(find)) == 0)
			return (j);
		else
			j++;
	}
	return (-1);
}

int main(int argc, char **argv, char **envp)
{
	char *input;
	char **commands;
	char *path;

	while (1)
	{
		input = readline("\033[34mminishell -> \033[0m");

		if (!(ft_strncmp(input,"\0", 1) == 0))
		{
			commands = ft_split(input, ' ');
			if (ft_strlen(input) > 0)
				add_history(input);
			if (ft_strncmp(commands[0], "exit",4) == 0)
			{
				printf("\033[31mExiting minishell...\n");
				free(commands);
				free(input);
				exit(0);
			}
			if (ft_strncmp(commands[0],"cd", 2) == 0)
			{
				if (commands[1])
					chdir(commands[1]);
			}
			else
			{
				pid_t pid = fork();
				path = ft_strjoin("/bin/", commands[0]);
				if (pid == 0)
				{
					if (execve(path, commands, envp) == -1)
						printf("\033[31mInvalid command \033[0m\n");
					exit(1);
				}
				else
					waitpid(pid, NULL, 0);
			}
		}
		free(input);
	}
}