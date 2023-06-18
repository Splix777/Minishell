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