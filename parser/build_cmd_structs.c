#include "../include/minishell.h"

static int count_args(t_token *tkn)
{
    int     count;
    t_token *tmp;

    count = 0;
    tmp = tkn;
    while (tmp->type == COMMAND_ARG && tmp->next)
    {
        count++;
        tmp = tmp->next;
    }
    return (count);
}

static void    print_cmd_token(t_minishell *minishell)
{
    t_command  *cmd;

    cmd = minishell->command;
    while (cmd)
    {
        printf("cmd: %s\n", cmd->cmd);
        printf("cmd_args: ");
        for (int i = 0; cmd->cmd_args[i]; i++)
            printf("%s ", cmd->cmd_args[i]);
        printf("\n");
        printf("redir: ");
        while (cmd->redir)
        {
            printf("type: %d, file: %s\n", cmd->redir->type, cmd->redir->file);
            cmd->redir = cmd->redir->next;
        }
        printf("\n");
        cmd = cmd->next;
    }
}

void    build_command_structs(t_minishell *minishell)
{
    t_token     *tkn;
    t_command   *cmd;
    t_redir     *redir;
    int         arg_count;
    int        i;

    tkn = minishell->tokens;
    cmd = malloc(sizeof(t_command));
    while (tkn)
    {
        if (tkn->type == COMMAND)
            cmd->cmd = ft_strdup(tkn->token);
        else if (tkn->type == COMMAND_ARG)
        {
            arg_count = 0;
            arg_count = count_args(tkn);
            cmd->cmd_args = malloc(sizeof(char *) * (arg_count + 1));
            i = 0;
            while (i < arg_count)
            {
                cmd->cmd_args[arg_count] = ft_strdup(tkn->token);
                i++;
                if (tkn->next)
                    tkn = tkn->next;
            }
            cmd->cmd_args[i] = NULL;
        }
        else if (tkn->type == REDIR_IN || tkn->type == REDIR_OUT || tkn->type == APPEND || tkn->type == HEREDOC)
        {
            redir = malloc(sizeof(t_redir));
            redir->type = tkn->type;
            redir->file = ft_strdup(tkn->next->token);
            redir->next = NULL;
            add_redir(&cmd->redir, redir);
            redir = redir->next;
        }
        else if (tkn->type == PIPE)
        {
            add_cmd(&minishell->command, cmd);
            cmd->next = malloc(sizeof(t_command));
            cmd = cmd->next;
        }
        if (tkn->next)
            tkn = tkn->next;
        break ;
    }
    printf("build_command_structs\n");
    print_cmd_token(minishell);
}
