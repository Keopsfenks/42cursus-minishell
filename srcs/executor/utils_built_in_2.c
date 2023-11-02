/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_built_in_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segurbuz <segurbuz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 08:46:21 by ogenc             #+#    #+#             */
/*   Updated: 2023/11/03 00:39:40 by segurbuz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_p_env_ex(t_exec *data)
{
	int		i;
	t_arg	*tmp;

	i = 0;
	tmp = g_data.exp_p;
	while (data->env_p[i])
	{
		printf("declare -x %s\n", data->env_p[i]);
		i++;
	}
	while (tmp != NULL)
	{
		if (find_env_dir(data->env_p, tmp->content) == -1)
			printf("declare -x %s\n", tmp->content);
		tmp = tmp->next;	
	}
}

char	*find_access(t_exec *data, char *input)
{
	char	**env_path;
	char	*str;
	char	*str_a;
	int		x;
	int		i;

	x = find_env_dir(data->env_p, "PATH");
	if (x != -1)
	{
		env_path = ft_split(data->env_p[x] + 5, ':');
		i = 0;
		while (env_path[i])
		{
			str_a = ft_strjoin(env_path[i], input);
			if (access(str_a, F_OK) == 0)
			{
				str = env_path[i];
				str = ft_strjoin(str, "/");
				free_commands(env_path);
				free(str_a);
				return (str);
			}
			free(str_a);
			i++;
		}
		free_commands(env_path);
	}
	return ("error");
}

void	set_envp(t_exec *data, char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
		i++;
	g_data.env_size = i;
	data->env_p = ft_calloc(1024, sizeof(char *));
	i = 0;
	while (envp[i])
	{
		data->env_p[i] = ft_strdup(envp[i]);
		i++;
	}
	data->env_p[i] = NULL;
	g_data.envp = data->env_p;
}

char	*ft_f_command(char *command)
{
	char	*n_str;
	int		i;

	i = 0;
	while ((command[i] >= 'A' && command[i] <= 'Z') \
			|| (command[i] >= 'a' && command[i] <= 'z'))
		i++;
	if (command[0] != '=')
	{
		n_str = malloc(sizeof(char) * i + 1);
		ft_strlcpy(n_str, command, i + 1);
	}
	else
		return (NULL);
	return (n_str);
}
