/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segurbuz <segurbuz@student.42istanbul.co>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 15:28:25 by segurbuz          #+#    #+#             */
/*   Updated: 2023/09/12 06:29:51 by segurbuz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libary/libft/libft_extras.h"
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
	int	dollar;
	int	rdr;
	int	heredoc;
	int	word;
	int	pipe;
}		t_counter;

typedef struct s_data
{
	t_counter	*counter;
	t_arg		*list;
	char		*line;
	char		**envp;
	char		**redirection;
	int			error_flag;
	int			quot;
}				t_data;

t_data	*g_data;

void	*ft_parse(void);
void	*removed_space_quot(t_arg **tmp);
void	split_redirections_pipe(t_arg **line);
void	freelizer(t_arg *free);
int		is_check(char c);
void	struct_initilaize(int rule);

#endif
