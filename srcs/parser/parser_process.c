/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segurbuz <segurbuz@student.42istanb>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 15:28:25 by segurbuz          #+#    #+#             */
/*   Updated: 2023/09/14 17:20:23 by segurbuz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	*splitting_to_add_list(t_arg *temp, char *str)
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
				return (g_data.error_flag = -1, (void *)-1);
			if (ft_isprint(str[i - 1]))
				ft_lstadd_back(&temp, \
				ft_lstnew(0, ft_substr(str, start, i - start)));
			ft_lstadd_back(&temp, ft_lstnew(0, ft_substr(str, i, 1)));
			start = i + 1;
		}
		else if (g_data.quot != 1 && (str[i] == '<' || str[i] == '>'))
		{
			if (str[i + 1] == '|')
				return (g_data.error_flag = -1, (void *)-1);
			if (str[i + 1] == '<' || str[i + 1] == '>')
			{
				counter = 2;
				if (str[i + 2] == '<' || str[i + 2] == '>' || str[i + 2] == '|')
					return (g_data.error_flag = -1, (void *)-1);
			}
			if (ft_isprint(str[i - 1]))
				ft_lstadd_back(&temp, \
				ft_lstnew(0, ft_substr(str, start, i - start)));
			ft_lstadd_back(&temp, ft_lstnew(0, ft_substr(str, i, counter)));
			start = i + counter;
			counter = 1;
			i++;
		}
	}
	if (str[ft_strlen(str) - 1] != '|'
		&& str[ft_strlen(str) - 1] != '>' && str[ft_strlen(str) - 1] != '<')
		ft_lstadd_back(&temp, ft_lstnew(0, ft_substr(str, start, i - start)));
	return (free(str), (void *)1);
}


void	split_line(t_arg *temp, char *str)
{
	int	i;
	int	start;

	i = -1;
	start = 0;
	while (++i || 1)
	{
		if (is_check(str[i]) != 1 && (!str[i] || str[i] == ' '))
		{
			splitting_to_add_list(temp, ft_substr(str, start, i - start));
			while (str[i] == ' ' || !str[i])
				i++;
			i--;
			start = i + 1;
		}
		else if (str[i] == '#')
			return ;
		if (str[i] == '\0')
		{
			if (g_data.quot == 1)
				g_data.error_flag = -1;
			break ;
		}
	}
	free(str);
}

void	test(t_arg **temp)
{
	t_arg	*tmp;

	tmp = *temp;
	while (tmp != NULL)
	{
		printf("list: %s;\n", tmp->content);
		tmp = tmp->next;
	}
}

char	*path_add_dollars(char *str, char *path, char *dollar)
{
	char	*str_start;
	char	*new_str;
	char	*str_end;
	int		i;

	i = 0;
	while (str[i] != '$' && str[i] != '\0')
		i++;
	str_start = ft_substr(str, 0, i);
	str_end = ft_substr(str, (ft_strlen(path) + i) + 1, ft_strlen(str) - i);
	i = -1;
	while (str[++i] != '\0')
	{
		if (is_check(str[i]) <= 1 && str[i] == '$')
		{
			if (g_data.quot_type == '\'')
				path = ft_strjoin(dollar, path);
			else
				path = path_find(path);
			break ;
		}
	}
	new_str = ft_strjoin(str_start, path);
	new_str = ft_strjoin(new_str, str_end);
	free(g_data.line);
	g_data.line = new_str;
	return (new_str);
}

void	find_path_name()
{
	int		i;
	int		len;
	char	*path;

	i = -1;
	len = 1;
	while (g_data.line[++i] != '\0')
	{
		if (g_data.line[i - 1] == '$')
		{
			len = 1;
			while (len++ && path_check(g_data.line[i]))
			{
				if (!path_check(g_data.line[i]))
					break ;
				i++;
			}
			path = ft_substr(g_data.line, (i - len) + 2, len - 2);
			path_add_dollars(g_data.line, path, ft_strdup("$"));
		}
	}
}

void	ft_parse(void)
{
	t_arg	*temp;
	t_arg	*tmp;

	temp = malloc(sizeof(t_arg));
	temp->next = NULL;
	find_path_name();
	g_data.quot_type = 1000;
	g_data.quot = 0;
	split_line(temp, ft_strtrim(g_data.line, " "));
	if (g_data.error_flag == -1)
	{
		printf("HATA\n");
		g_data.error_flag = 0;
		g_data.quot = 0;
		return ;
	}
	struct_initilaize(NULL, 0);
	ft_lstadd_back(&temp, NULL);
	tmp = temp;
	temp = temp->next;
	check_quot_list(temp);
	free(tmp);
	g_data.list = temp;
	test(&g_data.list);
	freelizer(&temp);
}
