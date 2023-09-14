/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segurbuz <segurbuz@student.42istanb>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 01:04:15 by segurbuz          #+#    #+#             */
/*   Updated: 2023/09/02 18:54:38 by segurbuz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	freelizer(t_arg **line)
{
	t_arg	*tmp;

	tmp = *line;
	for (int i = 0; (*line) != NULL; ++i) {
		free((*line)->content);
		free(*line);
		(*line) = (*line)->next;
	}
}

int	is_check(char c)
{
	static int	rule = 1000;
	if (g_data.quot == 0 && (c == '\"' || c == '\''))
		rule = c;
	if (c == rule)
		g_data.quot += 1;
	return (g_data.quot);
}