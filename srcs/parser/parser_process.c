/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segurbuz <segurbuz@student.42istanb>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 15:28:25 by segurbuz          #+#    #+#             */
/*   Updated: 2023/09/09 15:42:05 by segurbuz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_check(char c)
{
	static char	rule = ' ';

	if (g_data->quot == 0 && (c == '\"' || c == '\''))
		rule = c;
	if (c == rule)
	{
		g_data->quot += 1;
	}
	return (g_data->quot);
}

void	splitting_to_add_list(t_arg *temp, char *str)
{
	int		i;
	int		start;
	int		counter;

	i = -1;
	start = 0;
	counter = 1;
	while (str[++i] != '\0')
	{
		if (is_check(str[i]) != 1 && str[i] == '|')
		{
			if (str[i + 1] == '|' || str[i + 1] == '<' || str[i + 1] == '>')
			{
				g_data->error_flag = -1;
				return ;
			}
			if (ft_isprint(str[i - 1]))
				ft_lstadd_back(&temp, ft_lstnew(ft_substr(str, start, i - start)));
			ft_lstadd_back(&temp, ft_lstnew(ft_substr(str, i, 1)));
			start = i + 1;
		}
		else if (g_data->quot != 1 && (str[i] == '<' || str[i] == '>'))
		{
			if (str[i + 1] == '|')
			{
				g_data->error_flag = -1;
				return ;
			}
			if (str[i + 1] == '<' || str[i + 1] == '>')
			{
				counter = 2;
				if (str[i + 2] == '<' || str[i + 2] == '>' || str[i + 2] == '|')
				{
					g_data->error_flag = -1;
					return ;
				}
			}
			if (ft_isprint(str[i - 1]))
				ft_lstadd_back(&temp, ft_lstnew(ft_substr(str, start, i - start)));
			ft_lstadd_back(&temp, ft_lstnew(ft_substr(str, i, counter)));
			start = i + counter;
			counter = 1;
			i++;
		}
		if (g_data->quot >= 2)
			g_data->quot = 0;
	}
	if (str[ft_strlen(str) - 1] != '|'
		&& str[ft_strlen(str) - 1] != '>' && str[ft_strlen(str) - 1] != '<')
		ft_lstadd_back(&temp, ft_lstnew(ft_substr(str, start, i - start)));
	free(str);
}

void	split_line(t_arg *temp, char *str)
{
	int	i;
	int	start;

	i = -1;
	start = 0;
	str[ft_strlen(str)] = ' ';
	while (str[++i] != '\0')
	{
		if (str[i] == ' ')
		{
			g_data->quot = 0;
			splitting_to_add_list(temp, ft_substr(str, start, i - start));
			start = i + 1;
		}
		else if (str[i] == '\"')
		{
			i += 2;
			while (str[i - 1] != '\"' && str[i - 1] != '\0')
				i++;
			if (str[i - 1] == '\0')
			{
				g_data->error_flag = -1;
				return ;
			}
			i--;
		}
		else if (str[i] == '\'')
		{
			i += 2;
			while (str[i - 1] != '\'' && str[i - 1] != '\0')
				i++;
			if (str[i - 1] == '\0')
			{
				g_data->error_flag = -1;
				return ;
			}
			i--;
		}
		else if (str[i] == '#')
			return ;
	}
}

void	*ft_parse(void)
{
	t_arg	*temp;

	temp = malloc(sizeof(t_arg));
	temp->next = NULL;
	split_line(temp, g_data->line);
	if (g_data->error_flag == -1)
	{
		printf("HATA\n");
		g_data->error_flag = 0;
		return ((void *)-1);
	}
	ft_lstadd_back(&temp, NULL);
	temp = temp->next;
	while (temp != NULL)
	{
		printf("list: %s;\n", temp->content);
		temp = temp->next;
	}
	free(temp);
	//printf("%d\n", i);
	return ((void *)0);
}