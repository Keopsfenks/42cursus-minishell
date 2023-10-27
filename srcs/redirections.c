/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segurbuz <segurbuz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 17:10:55 by segurbuz          #+#    #+#             */
/*   Updated: 2023/10/28 01:48:17 by segurbuz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

void    output_rdr(t_newlst *list, int i)
{ 
    g_data.out_fd = open(list->content[i + 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
    g_data.fdout = 1;
}

void    double_output_rdr(t_newlst *list, int i)
{ 
    g_data.out_fd = open(list->content[i + 1], O_CREAT | O_WRONLY | O_APPEND, 0644);
    g_data.fdout = 1;
}

void    input_rdr(t_newlst *list, int i)
{ 
    g_data.in_fd = open(list->content[i + 1], O_RDONLY, 0644);
    g_data.fdin = 1;
}

void    select_rdr_type(t_newlst *tmp, int i)
{
    tmp->content[i] = NULL;
    if (tmp->type[i] == OUTPUT_RDR)
        output_rdr(tmp, i);
    else if (tmp->type[i] == DOUBLE_OUTPUT_RDR)
        double_output_rdr(tmp, i);
    else if (tmp->type[i] == INPUT_RDR)
        input_rdr(tmp, i);
    else if (tmp->type[i] == DOUBLE_INPUT_RDR)
        double_input_rdr(tmp, i);
}

void    change_output_or_input(void)
{
    if (g_data.fdout == 1)
    {
        dup2(g_data.out_fd, 1);
        close(g_data.out_fd);
    }
    if (g_data.fdin == 1)
    {
        dup2(g_data.in_fd, 0);
        close(g_data.in_fd);
    } 
}

void	ft_exec_rdr(t_newlst **list)
{
	t_newlst	*tmp;
	int			i;

	tmp = *list;
	while (tmp != NULL)
	{
		i = -1;
		while (tmp->content[++i] != NULL)
		{
			if (tmp->type[i] != WORD)
			{
                select_rdr_type(tmp, i);
                i++;
			}
		}
		tmp = tmp->next;
	}
    change_output_or_input();
}
//cat < Makefile > a