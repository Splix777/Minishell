#include "../include/minishell.h"

void    free_structs(t_minishell *minishell)
{
    int exit_status;

    exit_status = minishell->exit_status;
    if (minishell->command != NULL)
        free(minishell->command);
    if (minishell->tokens != NULL)
        ft_tokenclear(&minishell->tokens);
    if (minishell->process != NULL)
        free(minishell->process);
    if (minishell->builtins != NULL)
        free(minishell->builtins);
    if (minishell->env != NULL)
        ft_envclear(&minishell->env);
    free(minishell);
    system("leaks minishell");
    exit(0);
}

int line_empty(char *line)
{
    int i;

    i = 0;
    if (!line)
        return (TRUE);
    while (line[i])
    {
        if (line[i] != 32 && (line[i] < 9 || line[i] > 13))
            return (FALSE);
        i++;
    }
    return (TRUE);
}