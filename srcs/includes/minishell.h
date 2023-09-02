#ifndef MINISHELL_H
#define MINISHELL_H

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
	int			exit_flag;
}				t_data;

t_data	*g_data;

void	*ft_parse(void);
void	*removed_space_quot(t_arg **tmp);
void	freelizer(t_arg *free);

#endif
