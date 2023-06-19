#include "../include/minishell.h"

void    add_token(t_token **head, char *content, int type)
{
    t_token *new;
    t_token *last;

    new = malloc(sizeof(t_token));
    if (new == NULL)
        return ;
    new->token = content;
    new->type = type;
    new->next = NULL;
    if (*head == NULL)
        *head = new;
    else
    {
        last = *head;
        while (last->next != NULL)
            last = last->next;
        last->next = new;
    }
}

void ft_tokenclear(t_token **lst)
{
    t_token *cleanlst;
    t_token *temp;

    cleanlst = *lst;
    while (cleanlst)
    {
        temp = cleanlst->next;
        ft_tokendelone(cleanlst);
        cleanlst = temp;
    }
    *lst = NULL;
}

void ft_tokendelone(t_token *lst)
{
    if (!lst)
        return ;
    free(lst->token);
    free(lst);
}