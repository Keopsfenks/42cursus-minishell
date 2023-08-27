//
// Created by furkan can on 26.08.2023.
//

#ifndef MINISHELL_H
#define MINISHELL_H

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
}       t_counter;

typedef struct s_arg
{
    char    *content;
    int     type;
    struct s_arg *next;
}           t_arg;

typedef struct s_data
{
    t_counter *counter;
    t_arg     *list;
    char    *line;
    char    **envp;
    char    **redirection;
}           t_data;

t_data  *gdata;

void    ft_parse();

#endif
