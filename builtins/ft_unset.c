#include "../include/minishell.h"

void    ft_unset(t_minishell *minishell)
{
    t_env   *tmp;
    char    *name;

    tmp = minishell->env;
    while (tmp)
    {
        if (minishell->command->cmd_args[1] == NULL)
        {
            ft_putstr_fd("unset: not enough arguments\n", 2);
            minishell->exit_status = 1;
            return ;
        }
        else if (minishell->command->cmd_args[1] != NULL)
        {
            name = minishell->command->cmd_args[1];
            if (ft_strcmp(tmp->name, name) == TRUE)
            {
                ft_remove_env_node(minishell->env, tmp);
                free(name);
                minishell->exit_status = 0;
                return ;
            }
            tmp = tmp->next;
        }
    }
    minishell->exit_status = 0;
}