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

void	ft_error(char *str)
{
	printf("%s\n", str);
	g_data.error_flag = 0;
}

void	freelizer(t_arg **line)
{
	t_arg	*tmp;

	tmp = *line;
	while ((*line) != NULL)
	{
		free((*line)->content);
		free(*line);
		(*line) = (*line)->next;
	}
}

int	is_check(char c)
{
	if (g_data.quot == 0 && (c == '\"' || c == '\''))
		g_data.quot_type = c;
	if (c == g_data.quot_type)
		g_data.quot += 1;
	if (g_data.quot % 2 == 0)
	{
		g_data.quot_type = 1000;
		g_data.quot = 0;
	}
	return (g_data.quot);
}

int	env_control(char *str, int i)
{
	while (str[i] != '\0')
	{
		is_check(str[i]);
		if (g_data.quot_type != '\'' && str[i] == '$')
			return (i);
		i++;
	}
	return (i);
}
