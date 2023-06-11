#include "minishell.c"

void    free_structs(t_minishell *minishell, int which)
{
    if (which == 1)
        free(minishell);
    if (which == 2)
    {
        free(minishell->t_command)
        free(minishell);
    }
    if (which == 3)
    {
        free(minishell->t_history);
        free(minishell->t_command);
        free(minishell);
    }
    if (which == 4)
    {
        free(minishell->t_process);
        free(minishell->t_history);
        free(minishell->t_command);
        free(minishell);
    }
    exit(1);
}