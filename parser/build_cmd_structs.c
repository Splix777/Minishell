#include "../include/minishell.h"

t_token handle_symbol(t_minishell *minishell, t_command *command)
{
    t_token *token;
    char    *symbol[];
    char    *symbol_type[];
    int     i;

    token = minishell->tokens;
    symbol = {"|", "<", ">", ">>", "<<", NULL};
    symbol_type = {"PIPE", "INPUT", "OUTPUT", "APPEND", "HERE_DOC", NULL};
    i = 0;
    if (token->type == SYMBOL)
    {
        while(symbol[i] && ft_strcmp(token->token, symbol[i]) != 0)
            i++;
        if (symbol[i])
        {
            token->type = symbol_type[i];
            if (i == 0)
                token = handle_pipe(minishell, command);
            else if (i == 1 || i == 2 || i == 3)
                token = handle_redirection(minishell, command, i);
            else if (i == 4)
                token = handle_here_doc(minishell, command);
        }
    }
    return (token);
}

void    build_command_structs(t_minishell *minishell)
{
    t_token     *token;
    t_command   *command;

    token = minishell->tokens;
    command = NULL;
    while (token)
    {
        if (token->type == SYMBOL)
            token = handle_symbol(minishell, command);
        while (token->type == COMMAND || token->type == DQUOTE || token->type == SQUOTE)
            token = handle_command(minishell);
    }
}