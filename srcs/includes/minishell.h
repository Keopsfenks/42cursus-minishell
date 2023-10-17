/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segurbuz <segurbuz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 15:28:25 by segurbuz          #+#    #+#             */
/*   Updated: 2023/10/17 15:50:41 by segurbuz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libary/libft/libft_extras.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <dirent.h>
# include <stdarg.h>
# include <string.h>
# include <stdbool.h>

typedef struct s_counter
{
	int	rdr;
	int	heredoc;
	int	pipe;
}		t_counter;

typedef struct s_list
{
	char			**content;
	int				type;
	struct s_list	*next;
}					t_list;

typedef struct s_data
{
	t_counter	*counter;
	t_arg		*list;
	t_list		*arg;
	char		*line;
	char		**envp;
	char		**redirection;
	int			error_flag;
	int			error_code;
	int			quot;
	int			quot_type;
}				t_data;

t_data	g_data;

void	ft_parse(void);
void	freelizer(t_arg **free);
int		is_check(char c);
void	struct_initilaize(char **envp, int rule);
bool	env_check(char const *str, char c, int rule);
char	*env_find(char *path);
void	check_quot_list(t_arg *temp);
char	*env_add_dollars(char *str, char *path);
int		env_control(char *str, int i);
void	ft_error(char *str);
void	change_list(t_arg *temp);
void	find_env_name(t_arg *temp);
void	parse_error(int error_code);
void	*error_check(t_arg *temp);

#endif
