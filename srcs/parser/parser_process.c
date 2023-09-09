/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segurbuz <segurbuz@student.42istanb>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 15:28:25 by segurbuz          #+#    #+#             */
/*   Updated: 2023/09/09 14:41:14 by segurbuz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	insert_with_quotation(t_arg *tmp, char *str)
{
	int		i;
	int		start;
	int		counter;
	int		len;

	i = -1;
	counter = 0;
	start = 0;
	len = 1;
	str[ft_strlen(str)] = ' ';
	while (str[++i] != '\0')
	{
		if (str[i] == ' ' || !str[i])
		{
			ft_lstadd_back(&tmp, ft_lstnew(ft_substr(str, start, len - 1)));
			while (str[i] == ' ' || !str[i])
				i++;
			i--;
			len = 0;
			start = i + 1;
		}
		if ((str[i] == '|' || str[i] == '<' || str[i] == '>')
			&& str[i - 1] != ' ' && str[i + 1] != ' ')
		{
			ft_lstadd_back(&tmp, ft_lstnew(ft_substr(str, start, len - 1)));
			while ((str[i] == '|' || str[i] == '<' || str[i] == '>') && len++)
			{
				counter++;
				i++;
			}
			if (counter >= 2)
				exit(1);
			ft_lstadd_back(&tmp, ft_lstnew(ft_substr(str, i, len)));
			len = 0;
			start = i + 1;
		}
		else if (str[i] == '\"' && len--)
		{
			while (str[++i] != '\"' == 1 && str[i])
				len++;
			start++;
			len--;
		}
		else if (str[i] == '\'' && len--)
		{
			while (str[++i] != '\'' == 1 && str[i])
				len++;
			start++;
		}
		len++;
	}
	free(str);
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
	if ((int )quotation_counter() == -1) // bozuk tırnak içindekilerinide sayıyor.
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

void	*ft_parse(void)
{
	t_arg	*temp;

	temp = malloc(sizeof(t_arg));
	temp->next = NULL;
	removed_space_quot(&temp);
	for (int i = 0; temp != NULL; ++i) {
		printf("%s;\n", temp->content);
		temp = temp->next;
	}
	return ((void *)0);
}