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

void    wait_childs(t_minishell *minishell, pid_t pid, int status)
{
    while (1)
    {
        pid = waitpid(pid, &status, 0);
        if (pid < 0)
            break ;
        if (WIFEXITED(status))
            minishell->exit_status = WEXITSTATUS(status);
        if (WIFSIGNALED(status))
            minishell->exit_status = WTERMSIG(status) + 128;
        if (pid == 0)
            break ;
    }
}