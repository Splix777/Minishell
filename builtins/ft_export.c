#include "../include/minishell.h"

void    do_export(t_minishell *minishell, int i)
{
    char    **a;
    char    *name;
    char    *val;
    t_env   *env;

    a = minishell->command->cmd_args;
    env = minishell->env;
    name = ft_substr(a[i], 0, ft_strchr(a[i], '=') - a[i]);
    val = ft_substr(a[i], ft_strchr(a[i], '=') - a[i] + 1, ft_strlen(a[i]));
    if (val[0] == '\0' && a[i + 1] != NULL)
    {
        free(val);
        val = ft_strdup(a[i + 1]);
    }
    if (find_env_var_node(minishell, name) == NULL)
        ft_add_env_node(&minishell->env, name, val);
    else
    {
        env = find_env_var_node(minishell, name);
        free(env->value);
        free(name);
        env->value = val;
    }
}

void    ft_export(t_minishell *minishell)
{
    int     i;

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
            do_export(minishell, i);
        i++;
    }
}