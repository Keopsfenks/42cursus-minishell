/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogenc <ogenc@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 14:18:57 by ogenc             #+#    #+#             */
/*   Updated: 2022/12/29 17:36:32 by ogenc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft_extras.h"

void	ft_lstclear(t_arg **lst, void (*del)(void *))
{
	t_arg	*tmp;

	while (*lst && lst)
	{
		tmp = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = tmp;
	}
	*lst = NULL;
}
