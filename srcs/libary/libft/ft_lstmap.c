/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogenc <ogenc@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 17:20:30 by ogenc             #+#    #+#             */
/*   Updated: 2022/12/29 17:38:28 by ogenc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_extras.h"

t_arg	*ft_lstmap(t_arg *lst, void *(*f)(void *), void (*del)(void *))
{
	t_arg	*new;
	t_arg	*tmp;

	new = 0;
	while (lst)
	{
		tmp = ft_lstnew(f(lst->content));
		if (!tmp)
		{
			ft_lstclear(&new, del);
			return (0);
		}
		ft_lstadd_back(&new, tmp);
		lst = lst->next;
	}
	return (new);
}
