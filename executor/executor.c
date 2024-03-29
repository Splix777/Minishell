#include "../include/minishell.h"

void    handle_redir(t_command *cmd, int fd)
{
    if (cmd->fdin < 0 || cmd->fdin < 0)
        exit(errno);
    if (cmd->fdin != STDIN_FILENO)
    {
        dup2(cmd->fdin, STDIN_FILENO);
        close(cmd->fdin);
    }
    if (cmd->fdout != STDOUT_FILENO)
    {
        dup2(cmd->fdout, STDOUT_FILENO);
        close (cmd->fdout);
    }
    else
        dup2(fd, STDOUT_FILENO);
}

void    create_pipe(t_minishell *minishell, t_command *cmd)
{
    int     fd[2];
    pid_t   pid;

    make_pipe(fd);
    pid = make_fork();
    if (pid == 0)
    {
        close(fd[READ_END]);
        handle_redir(cmd, fd[WRITE_END]);
        execute_cmd(minishell, cmd);
        close(fd[WRITE_END]);
    }
    if (cmd->fdin != STDIN_FILENO)
        close(cmd->fdin);
    if (cmd->fdout != STDOUT_FILENO)
        close(cmd->fdout);
    close(fd[WRITE_END]);
    dup2(fd[READ_END], STDIN_FILENO);
    close(fd[READ_END]);
}

void    execute_last_cmd(t_minishell *minishell, t_command *cmd)
{
    pid_t   pid;

    pid = make_fork();
    if (pid == 0)
	{
        if (cmd->fdin < 0 || cmd->fdout < 0)
            exit(errno);
        if (cmd->fdin != STDIN_FILENO)
            dup2(cmd->fdin, STDIN_FILENO);
        if (cmd->fdout != STDOUT_FILENO)
            dup2(cmd->fdout, STDOUT_FILENO);
        if (cmd->fdin != STDIN_FILENO)
            close(cmd->fdin);
        if (cmd->fdout != STDOUT_FILENO)
            close(cmd->fdout);
        execute_cmd(minishell, cmd);
	}
    close(cmd->fdin);
    close(cmd->fdout);
    close(STDIN_FILENO);
}

t_command   *multi_execute(t_minishell *minishell, t_command *cmd)
{
    open_fds(minishell, cmd);
    if (cmd->next)
        create_pipe(minishell, cmd);\
    else
        execute_last_cmd(minishell, cmd);
    return (cmd->next);
}

void    executor(t_minishell *minishell)
{
    t_command   *cmd;
    pid_t       pid;
    int         status;

    cmd = minishell->command;
    if (!minishell->command->next && is_builtin(minishell) == TRUE)
        execute_builtin(minishell);
    else
    {
        pid = make_fork();
        if (pid == 0)
        {
            while (cmd)
                cmd = multi_execute(minishell, cmd);
            while (waitpid(-1, &status, 0) > 0)
                exit(WEXITSTATUS(status));


        }
        waitpid(pid, &status, 0);
        wait_childs(minishell, pid, status);
    }
}