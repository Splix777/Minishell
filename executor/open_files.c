#include "../include/minishell.h"

int open_infile(char *file)
{
    int fd;

    fd = open(file, O_RDONLY);
    if (fd < 0)
        perror(file);
    return (fd);
}

int open_outfile(char *file)
{
    int fd;

    fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0)
        perror(file);
    return (fd);
}

int open_append(char *file)
{
    int fd;

    fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (fd < 0)
        perror(file);
    return (fd);
}

int    redir_loop(t_minishell *minishell, t_redir *redir, int error)
{
        if (redir->type == REDIR_IN && !error)
            minishell->command->fdin = open_infile(redir->file);
        else if ((redir->type == REDIR_OUT) && !error)
            minishell->command->fdout = open_outfile(redir->file);
        else if ((redir->type == APPEND) && !error)
            minishell->command->fdout = open_append(redir->file);
        else if (redir->type == HEREDOC)
            minishell->command->fdin = open_heredoc(minishell, redir->file);
        if (minishell->command->fdin < 0)
        {
            minishell->command->fdin = STDIN_FILENO;
            error = 1;
        }
        if (minishell->command->fdout < 0)
        {
            minishell->command->fdout = STDOUT_FILENO;
            error = 1;
        }
        if (redir->next && (redir->next->type == REDIR_IN || redir->next->type == HEREDOC) && !error)
            close(minishell->command->fdin);
        if (redir->next && (redir->next->type == REDIR_OUT || redir->next->type == APPEND) && !error)
            close(minishell->command->fdout);
        return (error);
}

void    open_fds(t_minishell *minishell, t_command *cmd)
{
    t_redir *redir;
    int     error;

    redir = cmd->redir;
    error = 0;
    while (redir)
    {
        error = redir_loop(minishell, redir, error);
        redir = redir->next;
    }
}