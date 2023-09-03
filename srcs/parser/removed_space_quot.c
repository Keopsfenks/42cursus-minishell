/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   removed_space.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segurbuz <segurbuz@student.42istanb>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 15:58:27 by segurbuz          #+#    #+#             */
/*   Updated: 2023/08/28 15:58:30 by segurbuz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_quotation(char *s)
{
	if (*s == '\"')
		return (1);
	else if ( *s == '\'')
		return (2);
	return (0);
}

void	*insert_with_quotation(t_arg *tmp, char *str)
{
	int		i;
	int		rule;
	int		len;

	i = -1;
	rule = 0;
	len = 1;

	str[ft_strlen(str)] = ' ';
	while (str[++i] != '\0')
	{
		if (str[i] == '\"' && len++)
			while (str[++i] != '\"' == 1 && str[i])
				len++;
		if (str[i] == '\'' && len++)
			while (str[++i] != '\'' == 1 && str[i])
				len++;
		if (str[i] == ' ' || !str[i])
		{
			ft_lstadd_back(&tmp, ft_lstnew(ft_substr(str, rule, len - 1)));
			rule = i + 1;
			len = 0;
		}
		len++;
	}
	free(str);
	return ((void *)1);
}

void	*quotation_counter(void)
{
	int	i;
	int	quot_size;

	i = 0;
	quot_size = 0;
	while (g_data->line[i] != '\0')
	{
		if (g_data->line[i] == '\"' || g_data->line[i] == '\'')
			quot_size++;
		i++;
	}
	if (quot_size % 2 != 0)
	{
		g_data->exit_flag = -1;
		return ((void *)-1);
	}
	return ((void *)1);
}

void	*removed_space_quot(t_arg **tmp)
{
	char	*line;
	t_arg	*temp;

	line = ft_strtrim(g_data->line, " ");
	free(g_data->line);
	g_data->line = line;
	if ((int )quotation_counter() == -1)
	{
		g_data->exit_flag = -1;
		return ((void *)-1);
	}
	insert_with_quotation(*tmp, g_data->line);
	temp = *tmp;
	*tmp = (*tmp)->next;
	free(temp);
	return ((void *)0);
}