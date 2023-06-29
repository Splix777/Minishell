#include "../include/minishell.h"

pid_t   make_fork(void)
{
    pid_t   pid;

    pid = fork();
    if (pid < 0)
    {
        perror("fork");
        exit(1);
    }
    return (pid);
}

void    make_pipe(int fd[2])
{
    int p;

    p = pipe(fd);
    if (p < 0)
    {
        perror("pipe");
        exit(1);
    }
}

void    wait_childs(t_minishell *minishell)
{
    while (1)
    {
        minishell->process->pid = waitpid(-1, &minishell->process->status, 0);
        if (minishell->process->pid < 0)
            break ;
        if (WIFEXITED(minishell->process->status))
            minishell->exit_status = WEXITSTATUS(minishell->process->status);
        if (WIFSIGNALED(minishell->process->status))
            minishell->exit_status = WTERMSIG(minishell->process->status) + 128;
        if (minishell->process->pid == 0)
            break ;
    }
}