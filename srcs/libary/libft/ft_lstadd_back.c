/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogenc <ogenc@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 13:30:10 by ogenc             #+#    #+#             */
/*   Updated: 2023/01/02 15:05:53 by ogenc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft_extras.h"

void	ft_lstadd_back(t_arg **lst, t_arg *new)
{
	t_arg	*tmp;

	tmp = ft_lstlast(*lst);
	if (!tmp)
		*lst = new;
	else
		tmp->next = new;
}
