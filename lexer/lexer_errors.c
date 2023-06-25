#include "../include/minishell.h"

int token_error(t_minishell *minishell, char *token, int type)
{
    ft_putstr_fd("minishell: syntax error near unexpected token ", 2);
    ft_putstr_fd("'", 2);
    if (type == REDIRECT)
        ft_putstr_fd("newline", 2);
    else if (type == PIPE || type == SYMBOL)
        ft_putstr_fd(token, 2);
    ft_putstr_fd("'\n", 2);
    minishell->exit_status = 2;
    return (FALSE);
}

int	parse_errors(t_minishell *minishell)
{
	t_token *tmp;

	tmp = minishell->tokens;
    if (tmp->type == PIPE)
        return (token_error(minishell, tmp->token, PIPE));
    else
    {
	    while (tmp)
        {
            if (tmp->type == PIPE && tmp->next == NULL)
                return (token_error(minishell, tmp->token, PIPE));
            if (tmp->type == REDIRECT && tmp->next == NULL)
                return (token_error(minishell, tmp->token, REDIRECT));
            if (tmp->type == PIPE && tmp->next && tmp->next->type == PIPE)
                return (token_error(minishell, tmp->next->token, SYMBOL));
            if (tmp->type == REDIRECT && tmp->next && tmp->next->type == REDIRECT)
                return (token_error(minishell, tmp->next->token, SYMBOL));
            tmp = tmp->next;
        }
    }
    return (TRUE);
}

int is_quote(char c)
{
    if (c == '\"' || c == '\'')
        return (TRUE);
    return (FALSE);
}

int is_special_character(char c)
{
    if (c == '|' || c == '<' || c == '>')// || c == '\'' || c == '\"')
        return (TRUE);
    return (FALSE);
}