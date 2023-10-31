/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segurbuz <segurbuz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 20:31:46 by segurbuz          #+#    #+#             */
/*   Updated: 2023/10/31 21:03:15 by segurbuz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

void	exec_pipes(t_exec *data)
{
	t_newlst	*list;
	pid_t		pid;
	int			fd[2];

	list = g_data.arg;
	while (list != NULL)
	{
		pipe(fd);
		pid = fork();
		if (!pid)
		{
			data->path = ft_join_m(data, list->content);
			if (list->next != NULL)
				dup2(fd[1], 1);
			execve(data->path, list->content, data->env_p);
		}
		waitpid(-1, &g_data.error_code, 0);
		dup2(fd[0], 0);
		close (fd[0]);
		close (fd[1]);
		list = list->next;
	}
	dup2(g_data.default_out, 1);
	dup2(g_data.default_in, 0);
}
