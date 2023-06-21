#include "../include/minishell.h"

t_token handle_symbol(t_minishell *minishell)
{
    
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
            token = handle_symbol(minishell);
        while (token->type == COMMAND || token->type == DQUOTE || token->type == SQUOTE)
            token = handle_command(minishell);
    }
}