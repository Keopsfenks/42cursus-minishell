/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segurbuz <segurbuz@student.42istanbul.co>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 18:38:56 by segurbuz          #+#    #+#             */
/*   Updated: 2023/09/17 18:38:56 by segurbuz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	path_check(char c)
{
	if (ft_isdigit(c) || ft_isalnum(c) || c == '_' || c == '?')
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
	if (path[1] == '?' && ft_strlen(path + 1) == 1)
		return ("returned-error:?");
	while (g_data.envp[++i])
	{
		if (ft_strncmp(g_data.envp[i], path + 1, ft_strlen(path + 1)) == 0
			&& path_size(g_data.envp[i]) <= (int)ft_strlen(path + 1))
			break ;
	}
	if (g_data.envp[i] == NULL)
		return ("\0");
	else
		return (g_data.envp[i] + path_size(path));
}

void	path_add_dollars(char *str, char *path)
{
	char	*str_start;
	char	*str_end;
	int		i;

	i = 0;
	struct_initilaize(NULL, 0);
	i = path_control(str, i);
	str_start = ft_substr(str, 0, i);
	str_end = ft_substr(str, (ft_strlen(path + 1) + i) + 1, ft_strlen(str) - i);
	i = -1;
	while (str[++i] != '\0')
	{
		if (g_data.quot_type != '\'' && str[i] == '$')
		{
			path = path_find(path);
			break ;
		}
	}
	free(g_data.line);
	g_data.line = ft_strjoin(str_start, path);
	g_data.line = ft_strjoin(g_data.line, str_end);
	free(str_end);
}
//"$USER" '$PATH' $PWD
void	find_path_name(void)
{
	int		i;
	int		len;
	char	*path;

	i = -1;
	len = 1;
	while (g_data.line[++i] != '\0')
	{
		is_check(g_data.line[i]);
		if (g_data.quot_type != '\'' && g_data.line[i] == '$')
		{
			len = 1;
			i++;
			while (len++ && path_check(g_data.line[i]))
			{
				if (!path_check(g_data.line[i]))
					break ;
				i++;
			}
			path = ft_substr(g_data.line, (i - len) + 1, len - 1);
			path_add_dollars(g_data.line, path);
			g_data.quot = 0;
			i = -1;
			free(path);
		}
	}
	struct_initilaize(NULL, 0);
}