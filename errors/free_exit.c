#include "../include/minishell.h"

void    free_structs(t_minishell *minishell)
{
    int exit_status;

    exit_status = minishell->exit_status;
    if (minishell->command != NULL)
        ft_cmdclear(&minishell->command);
    if (minishell->tokens != NULL)
        ft_tokenclear(&minishell->tokens);
    if (minishell->process != NULL)
        free(minishell->process);
    if (minishell->builtins != NULL)
        free(minishell->builtins);
    if (minishell->env != NULL)
        ft_envclear(&minishell->env);
    free(minishell);
    exit(exit_status);
}
