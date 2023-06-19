#include "../include/minishell.h"

void    ft_env(t_minishell *minishel)
{
    t_env *tmp;

    tmp = minishel->env;
    while (tmp)
    {
        printf("%s%s\n", tmp->name, tmp->value);
        tmp = tmp->next;
    }
    minishel->exit_status = 0;
}