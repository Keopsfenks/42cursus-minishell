/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogenc <ogenc@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 13:11:10 by ogenc             #+#    #+#             */
/*   Updated: 2023/01/02 11:21:35 by ogenc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_extras.h"

t_arg	*ft_lstlast(t_arg *lst)
{
	while (lst != NULL)
	{
		if (lst->next == NULL)
			return (lst);
		else
			lst = lst->next;
	}
	return (lst);
}
