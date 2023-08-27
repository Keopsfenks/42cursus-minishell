#include "./includes/minishell.h"

void    struct_initilaize(void)
{
    //envp eklenecek.
    gdata = malloc(sizeof(gdata));
}

int main(int ac, char **av, char **envp)
{
    struct_initilaize();
    while (1)
    {
        gdata->line = readline("minishell-$ ");
        ft_parse();
    }
}
