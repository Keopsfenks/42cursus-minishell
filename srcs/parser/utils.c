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
	while ((*line) != NULL)
	{
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
	if (g_data.quot % 2 == 0)
	{
		g_data.quot_type = 1000;
		g_data.quot = 0;
	}
	return (g_data.quot_type = rule, g_data.quot);
}

bool	path_check(char c)
{
	if (ft_isdigit(c) || ft_isalnum(c) || c == '_')
		return (true);
	return (false);
}

int	path_size(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '=')
			break ;
		i++;
	}
	return (i);
}

char	*path_find(char *path) // HATALI
{
	int	i;

	i = -1;
	while (g_data.envp[++i])
	{
		if (ft_strncmp(g_data.envp[i], path, ft_strlen(path)) == 0
			&& path_size(g_data.envp[i]) <= (int)ft_strlen(path))
			break ;
	}
	if (g_data.envp[i] == NULL)
		return (" ");
	else
		return (g_data.envp[i] + path_size(path) + 1);
}
