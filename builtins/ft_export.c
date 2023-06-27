#include "../include/minishell.h"

void    ft_export(t_minishell *minishell)
{
    t_env   *env;
    char    *name;
    char    *value;
    int     i;

    env = minishell->env;
    if (minishell->command->cmd_args == NULL)
    {
        ft_putstr_fd("export: not enough arguments\n", 2);
        minishell->exit_status = 1;
        return ;
    }
    i = 0;
    while (minishell->command->cmd_args[i])
    {
        if (ft_strchr(minishell->command->cmd_args[i], '='))
        {
            name = ft_substr(minishell->command->cmd_args[i], 0, ft_strchr(minishell->command->cmd_args[i], '=') - minishell->command->cmd_args[i]);
            value = ft_substr(minishell->command->cmd_args[i], ft_strchr(minishell->command->cmd_args[i], '=') - minishell->command->cmd_args[i] + 1, ft_strlen(minishell->command->cmd_args[i]));
            if (value[0] == '\0' && minishell->command->cmd_args[i + 1] != NULL)
            {
                value = ft_strdup(minishell->command->cmd_args[i + 1]);
                i++;
            }
            if (find_env_var_node(minishell, name) == NULL)
                ft_add_env_node(&minishell->env, name, value);
            else
            {
                env = find_env_var_node(minishell, name);
                free(env->value);
                free(name);
                env->value = value;
            }
        }
        i++;
    }
}