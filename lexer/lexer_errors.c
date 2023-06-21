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

int symbol_type(t_token *token)
{
    if (token->token[0] == '|')
        return (PIPE);
    else if (token->token[0] == '<' || token->token[0] == '>')
        return (REDIRECT);
    else
        return (FALSE);
}

int	parse_errors(t_minishell *minishell)
{
	t_token *tmp;

	tmp = minishell->tokens;
    if (tmp->type == SYMBOL && symbol_type(tmp) == PIPE)
        return (token_error(minishell, tmp->token, PIPE));
    else
    {
	    while (tmp)
        {
            if (tmp->type == SYMBOL && tmp->next == NULL && symbol_type(tmp) == PIPE)
                return (token_error(minishell, tmp->token, PIPE));
            if (tmp->type == SYMBOL && tmp->next == NULL && symbol_type(tmp) == REDIRECT)
                return (token_error(minishell, tmp->token, REDIRECT));
            if (tmp->type == SYMBOL && tmp->next && tmp->next->type == SYMBOL)
                return (token_error(minishell, tmp->next->token, SYMBOL));
            tmp = tmp->next;
        }
    }
    return (TRUE);
}