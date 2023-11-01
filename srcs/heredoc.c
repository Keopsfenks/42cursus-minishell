/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segurbuz <segurbuz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 00:33:47 by segurbuz          #+#    #+#             */
/*   Updated: 2023/11/01 05:53:55 by segurbuz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

void	double_input_rdr(t_newlst *tmp, int i)
{
	char	*input;
	char	*end_name;
	int		fd[2];
	pid_t	pid;
    
	pipe(fd);
	end_name = tmp->content[i + 1];
	pid = fork();
	if (!pid)
	{
		while (1)
		{
			input = readline("> ");
			if (!input)
			{
				g_data.in_rdr = 1;
				close(fd[0]);
				close(fd[1]);
				return ;
			}
			dup2(fd[1], 1);
			if (ft_strcmp(input, end_name) == 0)
			{
				free(input);
				dup2(g_data.default_out, 1);
				break ;
			}
			printf("%s\n", input);
			dup2(g_data.default_out, 1);
			free(input);
		}
		exit(0);
	}
	waitpid(-1, &g_data.error_code, 0);
	g_data.fd[0] = fd[0];
	g_data.fdin = 1;
	close(fd[1]);
}
