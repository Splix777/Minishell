#include "../include/minishell.h"

int count_args(t_token **tkn)
{
    int     count;
    t_token *tmp;

    count = 1;
    tmp = *tkn;
    while (tmp->type == COMMAND_ARG && tmp->next)
    {
        count++;
        tmp = tmp->next;
    }
    return (count);
}

// static void    print_cmd_token(t_minishell *minishell)
// {
//     t_command   *cmd;
//     t_redir     *redir;
//     int         i;

//     cmd = minishell->command;
//     while (cmd)
//     {
//         printf("\n");
//         printf("cmd: [%s]\n", cmd->cmd);
//         printf("    cmd_args:");
//         i = 0;
//         while (cmd->cmd_args && cmd->cmd_args[i])
//         {
//             printf("[%s]", cmd->cmd_args[i]);
//             i++;
//         }
//         printf("\n");
//         printf("redirs: \n");
//         redir = cmd->redir;
//         while (redir)
//         {
//             printf("    type: [%d], file: [%s]\n", redir->type, redir->file);
//             redir = redir->next;
//         }
//         printf("\n");
//         if (cmd->next == NULL)
//             break;
//         cmd = cmd->next;
//     }
// }

void    assign_args(t_command *cmd, t_token **tkn)
{
    int arg_count;
    int i;

    arg_count = count_args(tkn);
    cmd->cmd_args = malloc(sizeof(char *) * (arg_count + 1));
    if (!cmd->cmd_args)
        return ;
    memset(cmd->cmd_args, 0, sizeof(char *) * (arg_count + 1));
    i = 0;
    while ((*tkn)->type == COMMAND_ARG)
    {
        cmd->cmd_args[i] = ft_strdup((*tkn)->token);
        i++;
        if ((*tkn)->next && (*tkn)->next->type == COMMAND_ARG)
            *tkn = (*tkn)->next;
        else
            break ;
    }
    cmd->cmd_args[arg_count] = NULL;
}

void    assing_redirs(t_command *cmd, t_token **tkn)
{
    t_redir *redir;

    redir = malloc(sizeof(t_redir));
    if (!redir)
        return ;
    memset(redir, 0, sizeof(t_redir));
    redir->type = (*tkn)->type;
    redir->file = ft_strdup((*tkn)->next->token);
    redir->next = NULL;
    add_redir(&cmd->redir, redir);
}

void    build_command_structs(t_minishell *minishell)
{
    t_command   *cmd;
    t_token     *tkn;

    tkn = minishell->tokens;
    cmd = init_cmd();
    while (tkn)
    {
        if (tkn->type == COMMAND)
            cmd->cmd = ft_strdup(tkn->token);
        else if (tkn->type == COMMAND_ARG)
            assign_args(cmd, &tkn);
        else if (tkn->type == REDIR_IN || tkn->type == REDIR_OUT || tkn->type == APPEND || tkn->type == HEREDOC)
            assing_redirs(cmd, &tkn);
        else if (tkn->type == PIPE)
        {
            add_cmd(&minishell->command, cmd);
            cmd = cmd->next;
            cmd = init_cmd();
        }
        if (tkn->next == NULL)
            add_cmd(&minishell->command, cmd);
        tkn = tkn->next;
    }
    //print_cmd_token(minishell);
}
