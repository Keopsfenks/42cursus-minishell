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

void	struct_initilaize(int rule)
{
	//envp eklenecek.
	if (rule == 1)
		g_data = malloc(sizeof(g_data));
	g_data->error_flag = 0;
	g_data->quot = 0;
}

int main(int ac, char **av, char **envp)
{
	struct_initilaize(1);
	(void )envp;
	(void )av;
	(void )ac;
	while(1)
	{
		g_data->line = readline("minishell-$ ");
		add_history(g_data->line);
		ft_parse();
		free(g_data->line);
	}
	//system("leaks minishell");
}