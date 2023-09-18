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

int	quot_check(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\"' || str[i] == '\'')
			return (1);
		i++;
	}
	return (0);
}

int		new_str_lenght(char *str)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (str[i])
	{
		is_check(str[i]);
		if (str[i] == g_data.quot_type)
			while (str[++i] != g_data.quot_type)
				len++;
		else
			len++;
		i++;
	}
	return (len);
}

char	*trim_quot(char *str)
{
	int		len;
	char	*new_str;
	int		i;
	int		j;

	len = new_str_lenght(str);
	new_str = malloc(sizeof(char) * (len + 1));
	if (!new_str)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		is_check(str[i]);
		if (str[i] == g_data.quot_type)
			while (str[++i] != g_data.quot_type)
				new_str[j++] = str[i];
		else
			new_str[j++] = str[i];
		i++;
	}
	new_str[j] = '\0';
	return (new_str);
}

void	check_quot_list(t_arg *temp)
{
	t_arg	*tmp;
	char	*s;
	int		i;

	i = 0;
	tmp = temp;
	while (tmp != NULL)
	{
		if (quot_check(tmp->content))
		{
			s = tmp->content;
			tmp->content = trim_quot(tmp->content);
			free(s);
		}
		tmp = tmp->next;
	}
	g_data.quot = 0;
}

int path_control(char *str, int i)
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