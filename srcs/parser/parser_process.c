/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segurbuz <segurbuz@student.42istanb>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 15:28:25 by segurbuz          #+#    #+#             */
/*   Updated: 2023/08/28 15:40:47 by segurbuz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	tokenizer(t_arg *temp)
{
	char	*line;

	line = ft_strtrim(g_data->line, " ");
	free(g_data->line);
	g_data->line = line;
	removed_space_quot(temp);
	return (1);
}

void	*ft_parse(void)
{
	t_arg	*temp;

	temp = malloc(sizeof(t_arg));
	temp->next = NULL;
	if (tokenizer(temp) == -1)
	{
		g_data->exit_flag = -1;
		return ((void *)-1);
	}
	g_data->list = temp;
	g_data->list = g_data->list->next;
	//freelizer(temp); leak hatası ve abort yiyor.
	for (int i = 0; g_data->list != NULL; ++i) {
		printf("%s\n", g_data->list->content);
		g_data->list = g_data->list->next;
	}
	return ((void *)0);
}