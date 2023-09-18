/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segurbuz <segurbuz@student.42istanbul.co>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 00:05:04 by segurbuz          #+#    #+#             */
/*   Updated: 2023/09/12 00:05:44 by segurbuz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

void	envp_copy(char **envp)
{
	int		i;

	i = 0;
	while (envp[i])
		i++;
	g_data.envp = (char **)malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (envp[i])
	{
		g_data.envp[i] = ft_strdup(envp[i]);
		i++;
	}
	g_data.envp[i] = NULL;
}

void	struct_initilaize(char **envp, int rule)
{
	if (rule == 1)
		envp_copy(envp);
	g_data.error_flag = 0;
	g_data.quot = 0;
	g_data.quot_type = 1000;
}

int main(int ac, char **av, char **envp)
{
	struct_initilaize(envp, 1);
	(void )av;
	(void )ac;
	while(1)
	{
		g_data.line = readline("minishell-$ ");
		add_history(g_data.line);
		ft_parse();
		free(g_data.line);
		struct_initilaize(NULL, 0);
		//system("leaks minishell");
	}
}
// $PATH $USER' '$PWD ABORT || leak var düzelt. tırnak içinde gelen anlamsız dollar silinicek.