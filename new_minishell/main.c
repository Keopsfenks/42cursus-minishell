/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogenc <ogenc@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 03:56:43 by ogenc             #+#    #+#             */
/*   Updated: 2023/08/30 03:56:44 by ogenc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	free_commands(char **commands)
{
	int x = -1;
	while (commands[++x])
		free(commands[x]);
	free(commands);
}

// TODO:
// env pathten aldıgım path verisinin bak: PATH=/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/munki
// buradaki pathin içerisindeki ':' leri split ile ayırarak
// access fonksiyonu ile girilen argümanın (örn ls) komutunun varlıgı kontrol edilecek
// var olan yolun tamamı alınıp execve ile çalıştırılacak örnek /bin/ içerisinde ls varlıgı kontrol edildi
// ve accessin döndürdügü dönüş degeri sayesinde /bin/ içerisinde oldugu dogrulandı execve ile çalıştırıldı.
// TODO 2:
// builtin fonksiyonları yazılacak, ayırılacak
// cd komutunun tek "cd" argümanında home dizini


int main(int argc, char **argv, char **envp)
{
	char *input;
	char **commands;
	char *path;
	char **env_path;

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
				printf("\033[31mExiting minishell...\033[0m\n");
				free_commands(commands);
				free(input);
				system("leaks a.out");
				exit(0);
			}
			if (ft_strncmp(commands[0],"cd", 2) == 0)
			{
				if (commands[1])
					if (chdir(commands[1]) == -1)
						printf("\033[31mcd: no such file or directory: %s\033[0m\n", commands[1]);
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
		free_commands(commands);
		free(path);
	}
}

