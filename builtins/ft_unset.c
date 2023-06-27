#include "../include/minishell.h"

void    ft_unset(t_minishell *minishell)
{
    t_env   *tmp;
    int     i;

    if (minishell->command->cmd_args == NULL)
    {
        ft_putstr_fd("unset: not enough arguments\n", 2);
        minishell->exit_status = 1;
        return ;
    }
    i = 0;
    tmp = minishell->env;
    while (minishell->command->cmd_args[i])
    {
        if (minishell->command->cmd_args[i] != NULL)
        {
            tmp = find_env_var_node(minishell, minishell->command->cmd_args[i]);
            if (tmp != NULL)
            {
                ft_remove_env_node(minishell->env, tmp);
                minishell->exit_status = 0;
            }
        }
        i++;
    }
    minishell->exit_status = 0;
}