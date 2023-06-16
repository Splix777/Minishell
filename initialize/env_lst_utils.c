#include "../include/minishell.h"

void add_env(t_env **head, t_env *env)
{
    t_env *node;

    if (*head)
    {
        node = ft_envlast(*head);
        node->next = env;
    }
    else
        *head = env;
}

t_env   *ft_envlast(t_env *lst)
{
    if (!lst)
        return (NULL);
    while (lst)
    {
        if (lst->next == NULL)
            return (lst);
        lst = lst->next;
    }
    return (lst);
}

void ft_envclear(t_env **lst)
{
    t_env *cleanlst;
    t_env *temp;

    cleanlst = *lst;
    while (cleanlst)
    {
        temp = cleanlst->next;
        ft_envdelone(cleanlst);
        cleanlst = temp;
    }
    *lst = NULL;
}

void ft_envdelone(t_env *lst)
{
    if (!lst)
        return ;
    free(lst->name);
    free(lst->value);
    free(lst);
}