/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_by_redirections_pipe.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segurbuz <segurbuz@student.42istanbul.co>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 06:28:31 by segurbuz          #+#    #+#             */
/*   Updated: 2023/09/04 20:08:43 by segurbuz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_arg	*find_pr(t_arg *line, char c)
{
	int		i;

	i = -1;
	while (line != NULL)
	{
		while (line->content[++i] != '\0')
		{
			if (line->content[i] == c)
			{
				if (ft_strlen(line->content) > 1)
					return (line);
			}
		}
		i = 0;
		line = line->next;
	}
	return (NULL);
}

int	pipe_redirections_quotcontrol(char *content, char c)
{
	int	i;
	int	len;

	i = -1;
	len = 0;
	while (content[++i] != '\0')
	{
		if (content[i] == '\"')
		{
			while (content[++i] != '\"')
			{
				if (content[i] == c)
					return (0);
			}
		}
	}
	return (1);
}
// echo "semih"| gurbuz araba
int	pipe_redirection_index(char *str, char c)
{
	int	i;

	i = -1;
	while (str[++i] != '\0')
	{
		if (str[i] == c)
			return (i);
	}
	return (0);
}

void	split_pipe_redirections(t_arg *line, char c)
{
	t_arg	*tmp;
	t_arg	*temp;
	int		index;

	tmp = find_pr(line, c);
	temp = tmp->next;
	if (tmp == NULL)
		return ;
	if (pipe_redirections_quotcontrol(tmp->content, c) == 0)
		return ;
	index = pipe_redirection_index(tmp->content, c);
}

void	split_redirections_pipe(t_arg **line)
{
	char	pr[4];
	int		i;

	i = -1;
	pr[0] = '|';
	pr[1] = '>';
	pr[2] = '<';
	pr[3] = '\0';
	split_pipe_redirections(*line, pr[0]);
}