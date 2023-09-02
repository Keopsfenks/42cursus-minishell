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

void	*insert_with_quotation(t_arg *tmp, char *str)
{
	int		i;
	int		rule;
	int		len;
	int		quot;

	i = -1;
	rule = 0;
	len = 0;
	quot = 0;
	if (str[ft_strlen(str) - 1] != '\"' && str[ft_strlen(str) - 1] != '\'')
		str[ft_strlen(str)] = ' ';
	while (str[++i] != '\0')
	{
		if (str[i] == ' ' || !str[i])
		{
			ft_lstadd_back(&tmp, ft_lstnew(ft_substr(str, rule, len)));
			while (str[i] == ' ')
				i++;
			rule = i;
			len = -1;
			i = i - 1;
		}
		else if (str[i] == '\"' || !str[i])
		{
			rule = i;
			while (str[++i] != '\"')
				quot++;
			ft_lstadd_back(&tmp, ft_lstnew(ft_substr(str, rule + 1, quot)));
			quot = 0;
		}
		else if (str[i] == '\'' || !str[i])
		{
			rule = i;
			while (str[++i] != '\'')
				quot++;
			ft_lstadd_back(&tmp, ft_lstnew(ft_substr(str, rule + 1, quot)));
			quot = 0;
		}
		len++;
	}
	free(str);
	return ((void *)1);
}

void	*quotation_counter(t_arg *tmp)
{
	int	i;
	int	quot_size;
	int	quot_size2;

	i = 0;
	quot_size = 0;
	quot_size2 = 0;
	while (g_data->line[i] != '\0')
	{
		if (g_data->line[i] == '\"')
			quot_size++;
		else if (g_data->line[i] == '\'')
			quot_size2++;
		i++;
	}
	if ((quot_size % 2 != 0 || quot_size2 % 2 != 0))
	{
		g_data->exit_flag = -1;
		return ((void *)-1);
	}
	else if ((int ) insert_with_quotation(tmp, g_data->line) == -1)
	{
		g_data->exit_flag = -1;
		return ((void *)-1);
	}
	tmp = tmp->next;
	return ((void *)1);
}

void	*removed_space_quot(t_arg *tmp)
{
	if ((int )quotation_counter(tmp) == -1)
	{
		g_data->exit_flag = -1;
		return ((void *)-1);
	}
	return ((void *)0);
}