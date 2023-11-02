/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segurbuz <segurbuz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 00:33:47 by segurbuz          #+#    #+#             */
/*   Updated: 2023/11/02 04:01:04 by segurbuz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

void	interrupt_here_document(int signal)
{
	(void)signal;
	write(1, "\n", 1);
	exit(errno);
}

void	double_input_rdr(t_newlst *tmp, int i)
{
	char	*input;
	char	*end_name;
	int		fd;	

	end_name = tmp->content[i + 1];
	fd = open(".heredoc.c", O_CREAT | O_RDWR | O_TRUNC, 0644);
	while (1)
	{
		input = readline("> ");
		dup2(fd, 1);
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
	g_data.input_name = ".heredoc.c";
	g_data.fdin = 1;
	close(fd);
}
