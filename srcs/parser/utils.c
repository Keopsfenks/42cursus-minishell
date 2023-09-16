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