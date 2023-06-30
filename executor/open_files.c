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

int    redir_loop(t_minishell *minishell, t_command *command , t_redir *redir, int error)
{
    (void)minishell;
    if (redir->type == REDIR_IN && !error)
        command->fdin = open_infile(redir->file);
    else if ((redir->type == REDIR_OUT) && !error)
        command->fdout = open_outfile(redir->file);
    else if ((redir->type == APPEND) && !error)
        command->fdout = open_append(redir->file);
    // else if (redir->type == HEREDOC)
    //     command->fdin = open_heredoc(minishell, redir->file);
    if (command->fdin < 0)
        error = 1;
    if (command->fdout < 0)
        error = 1;
    if (redir->next && (redir->next->type == REDIR_IN || redir->next->type == HEREDOC) && !error)
        close(command->fdin);
    if (redir->next && (redir->next->type == REDIR_OUT || redir->next->type == APPEND) && !error)
        close(command->fdout);
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
        error = redir_loop(minishell, cmd, redir, error);
        redir = redir->next;
    }
    
}