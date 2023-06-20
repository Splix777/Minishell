#include "../include/minishell.h"

void    ft_export(t_minishell *minishell)
{
    t_env   *env;
    t_env   *tmp;
    char    *name;
    char    *value;

    tmp = minishell->env;
    while (tmp)
    {
        if (minishell->command->cmd_args[1] == NULL)
        {
            ft_putstr_fd("export: not enough arguments\n", 2);
            minishell->exit_status = 1;
            return ;
        }
        else if (minishell->command->cmd_args[1] != NULL)
        {
            name = ft_substr(minishell->command->cmd_args[1], 0, ft_strchr(minishell->command->cmd_args[1], '=') - minishell->command->cmd_args[1]);
            value = ft_substr(minishell->command->cmd_args[1], ft_strchr(minishell->command->cmd_args[1], '=') - minishell->command->cmd_args[1] + 1, ft_strlen(minishell->command->cmd_args[1]));
            if (ft_strcmp(tmp->name, name) == 0)
            {
                free(tmp->value);
                tmp->value = ft_strdup(value);
                minishell->exit_status = 0;
                return ;
            }
            tmp = tmp->next;
        }
    }
    env = malloc(sizeof(t_env));
    env->name = ft_substr(minishell->command->cmd_args[1], 0, ft_strchr(minishell->command->cmd_args[1], '=') - minishell->command->cmd_args[1]);
    env->value = ft_substr(minishell->command->cmd_args[1], ft_strchr(minishell->command->cmd_args[1], '=') - minishell->command->cmd_args[1] + 1, ft_strlen(minishell->command->cmd_args[1]));
    env->next = NULL;
    add_env(&minishell->env, env);
    minishell->exit_status = 0;
}