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

void	splitting_to_add_list(t_arg *temp, char *str)
{
	int	i;
	int	start;
	int	counter;

	i = -1;
	start = 0;
	counter = 1;
	while (str[++i] != '\0')
	{
		if (str[i] == '|')
		{
			if (str[i + 1] == '|' )
			{
				g_data->error_flag = -1;
				return ;
			}
			if (!(ft_strlen(str) <= 2) && str[0] != '|')
				ft_lstadd_back(&temp, ft_lstnew(ft_substr(str, start, i - start)));
			ft_lstadd_back(&temp, ft_lstnew(ft_substr(str, i, 1)));
			start = i + 1;
		}
		else if (str[i] == '<' || str[i] == '>')
		{
			if (str[i + 1] == '<' || str[i + 1] == '>')
			{
				counter = 2;
				if (str[i + 2] == '<' || str[i + 2] == '>')
				{
					g_data->error_flag = -1;
					return ;
				}
			}
			if (!(ft_strlen(str) <= 2) && str[0] != '<' && str[0] != '>')
				ft_lstadd_back(&temp, ft_lstnew(ft_substr(str, start, i - start)));
			ft_lstadd_back(&temp, ft_lstnew(ft_substr(str, i, counter)));
			counter = 0;
			start = i + 1;
			i++;
		}
	}
	if (!(ft_strlen(str) <= 2) && str[ft_strlen(str) - 1] != '|'
		&& str[ft_strlen(str) - 1] != '>' && str[ft_strlen(str) - 1] != '<')
		ft_lstadd_back(&temp, ft_lstnew(ft_substr(str, start, i - start)));
	free(str);
}

void	split_line(t_arg *temp, char *str)
{
	int	i;
	int	start;

	i = 0;
	start = 0;
	str[ft_strlen(str)] = ' ';
	while (str[i] != '\0')
	{
		if (str[i] == ' ')
		{
			splitting_to_add_list(temp, ft_substr(str, start, i - start));
			start = i + 1;
		}
		i++;
	}
} // aasd|asdasd aasd 13

void	*ft_parse(void)
{
	t_arg	*temp;

	temp = malloc(sizeof(t_arg));
	temp->next = NULL;
	split_line(temp, g_data->line);
	if (g_data->error_flag == -1)
	{
		//mesaj;
		return ((void *)-1);
	}
	ft_lstadd_back(&temp, NULL);
	temp = temp->next;
	while (temp != NULL)
	{
		printf("%s\n", temp->content);
		temp = temp->next;
	}
	return ((void *)0);
}