#include "../include/minishell.h"

void    executor(t_minishell *minishell)
{
    //pid_t   pid;
    //int     status;

    if (!minishell->command->next && is_builtin(minishell) == TRUE)
        execute_builtin(minishell);
}