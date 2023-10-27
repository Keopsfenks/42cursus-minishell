/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segurbuz <segurbuz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 00:33:47 by segurbuz          #+#    #+#             */
/*   Updated: 2023/10/28 01:33:43 by segurbuz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

void	double_input_rdr(t_newlst *tmp, int i)
{
	char	*input;
	int		fdout;
	int		fdin;
	char	*end_name;
	int		fd[2];

	fdout = dup(1);
	fdin = dup(0);
	pipe(fd);
	end_name = tmp->content[i + 1];
	while (1)
	{
		input = readline("> ");
		dup2(fd[1], 1);
		if (ft_strcmp(input, end_name) == 0)
		{
			free(input);
			dup2(fdout, 1);
			break ;
		}
		printf("%s\n", input);
		dup2(fdout, 1);
        close(fdin);
		free(input);
	}
	dup2(fd[0], 0);
    g_data.out_fd = fd[0];
	close(fd[1]);
	close(fd[0]);
}
