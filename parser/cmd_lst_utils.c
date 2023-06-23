#include "../include/minishell.h"

void add_cmd(t_command **head, t_command *cmd)
{
    t_command *node;

    if (*head)
    {
        node = ft_cmdlast(*head);
        node->next = cmd;
    }
    else
        *head = cmd;
}

t_command   *ft_cmdlast(t_command *lst)
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

void ft_cmdclear(t_command **lst)
{
    t_command *cleanlst;
    t_command *temp;

    cleanlst = *lst;
    while (cleanlst)
    {
        temp = cleanlst->next;
        ft_cmddelone(cleanlst);
        cleanlst = temp;
    }
    *lst = NULL;
}

void ft_cmddelone(t_command *lst)
{
    if (!lst)
        return ;
    free(lst->cmd);
    ft_free_array(lst->cmd_args);
    // ft_redirclear(&lst->redir);
    free(lst);
}

void ft_remove_cmd_node(t_command *lst, t_command *node)
{
    t_command *tmp;

    tmp = lst;
    while (tmp)
    {
        if (tmp->next == node)
        {
            tmp->next = node->next;
            ft_cmddelone(node);
            break ;
        }
        tmp = tmp->next;
    }
}