#include "../include/minishell.h"

int open_infile(char *file)
{
    int fd;

    fd = open(file, O_RDONLY);
    return (fd);
}

int open_outfile(char *file)
{
    int fd;

    fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    return (fd);
}

int open_append(char *file)
{
    int fd;

    fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
    return (fd);
}

void    open_fds(t_minishell *minishell, t_command *cmd)
{
    t_redir *redir;
    int     error;

    redir = cmd->redir;
    error = 0;
    if (!redir)
    {
        cmd->fdin = STDIN_FILENO;
        cmd->fdout = STDOUT_FILENO;
    }
    while (redir)
    {
        if ((redir->type == REDIR_IN) && !error)
            cmd->fdin = open_infile(redir->file);
        else if ((redir->type == REDIR_OUT) && !error)
            cmd->fdout = open_outfile(redir->file);
        else if ((redir->type == APPEND) && !error)
            cmd->fdout = open_append(redir->file);
        else if (redir->type == HEREDOC)
            cmd->fdin = open_heredoc(minishell, redir->file);
        if (cmd->fdin < 0 || cmd->fdout < 0)
        {
            error = 1;
            perror(redir->file);
        }
        if (redir->next && (redir->next->type == REDIR_IN || redir->next->type == HEREDOC))
            close(cmd->fdin);
        if (redir->next && (redir->next->type == REDIR_OUT || redir->next->type == APPEND))
            close(cmd->fdout);
        redir = redir->next;
    }
}