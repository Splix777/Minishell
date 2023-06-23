#include "../include/minishell.h"

void add_redir(t_redir **head, t_redir *redir)
{
    t_redir *node;

    if (*head)
    {
        node = ft_redir_last(*head);
        node->next = redir;
    }
    else
        *head = redir;
}

t_redir *ft_redir_last(t_redir *lst)
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

void ft_redirclear(t_redir **lst)
{
    t_redir *cleanlst;
    t_redir *temp;

    cleanlst = *lst;
    while (cleanlst)
    {
        temp = cleanlst->next;
        ft_redirdelone(cleanlst);
        cleanlst = temp;
    }
    *lst = NULL;
}

void ft_redirdelone(t_redir *lst)
{
    if (!lst)
        return ;
    free(lst->file);
    free(lst);
}

void ft_remove_redir_node(t_redir *lst, t_redir *node)
{
    t_redir *tmp;

    tmp = lst;
    while (tmp)
    {
        if (tmp->next == node)
        {
            tmp->next = node->next;
            ft_redirdelone(node);
            break ;
        }
        tmp = tmp->next;
    }
}