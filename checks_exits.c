#include "minishell.h"

void    free_structs(t_minishell *minishell, int which)
{
    if (which == 1)
        free(minishell);
    if (which == 2)
    {
        free(minishell->command);
        free(minishell);
    }
    if (which == 3)
    {
        free(minishell->history);
        free(minishell->command);
        free(minishell);
    }
    if (which == 4)
    {
        free(minishell->process);
        free(minishell->history);
        free(minishell->command);
        free(minishell);
    }
    if (which == 5)
    {
        free(minishell->env);
        free(minishell->process);
        free(minishell->history);
        free(minishell->command);
        free(minishell);
    }
    exit(1);
}