/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogenc <ogenc@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 13:07:38 by ogenc             #+#    #+#             */
/*   Updated: 2023/09/18 06:00:39 by segurbuz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft_extras.h"

t_arg	*ft_lstnew(int type, void *content)
{
	t_arg	*lst;

	lst = malloc(sizeof(t_arg));
	if (!lst)
		return (NULL);
	lst->content = content;
	lst->type = type;
	lst->next = NULL;
	return (lst);
}
