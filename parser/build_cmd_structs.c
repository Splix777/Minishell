#include "../include/minishell.h"


void    build_command_structs(t_minishell *minishell)
{
    t_token     *token;
    t_command   *command;


    token = minishell->tokens;
    while (token)
    {
        while  (token->type == COMMAND || token->type)
    }
    (void) minishell;
}