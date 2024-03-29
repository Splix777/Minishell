#include "../include/minishell.h"

int ft_envsize(t_env *env)
{
    int i;
    t_env *tmp;

    i = 0;
    tmp = env;
    while (tmp)
    {
        i++;
        tmp = tmp->next;
    }
    return (i);
}

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

void ft_remove_env_node(t_env *lst, t_env *node)
{
    t_env *tmp;

    tmp = lst;
    while (tmp)
    {
        if (tmp->next == node)
        {
            tmp->next = node->next;
            ft_envdelone(node);
            return ;
        }
        tmp = tmp->next;
    }
}

void ft_add_env_node(t_env **head, char *name, char *value)
{
    t_env *node;

    node = malloc(sizeof(t_env));
    node->name = name;
    node->value = value;
    node->next = NULL;
    add_env(head, node);
}
