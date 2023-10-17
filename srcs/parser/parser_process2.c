/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_process2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segurbuz <segurbuz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 21:13:10 by segurbuz          #+#    #+#             */
/*   Updated: 2023/10/17 09:45:33 by segurbuz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int array_size(t_arg *temp)
{
	int	i;

	i = 0;
	while (temp != NULL)
	{
		if (temp->content[0] == '|' \
			|| temp->content[0] == '\0')
			break ;
		i++;
		temp = temp->next;
	}
	return (i);
}

t_arg	*add_list(t_list **list, t_arg *tmp, int size)
{
	t_list	*arg;
	int		i;

	i = -1;
	arg = *list;
	arg->content = malloc(sizeof(char *) * (size + 1));
	while (++i < size)
	{
		arg->content[i] = ft_strdup(tmp->content);
		tmp = tmp->next;
	}
	arg->content[size] = NULL;
	return (tmp);
}

void change_list(t_arg *temp) 
{
    t_list	*list;
    t_list	*headlst;
    int		size;

    list = malloc (sizeof(t_list));
	headlst = list;

    while (temp != NULL) 
	{
        size = array_size(temp);
        temp = add_list(&list, temp, size);
        if (temp != NULL) 
		{
            temp = temp->next;
            list->next = malloc(sizeof(t_list));
            list = list->next;
        }
    }
	g_data.arg = headlst;
}

// echo semih gurbuz | grep semih