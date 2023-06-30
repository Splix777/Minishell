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
    (void) pid;
    if (WIFSIGNALED(status))
    {
        if (WTERMSIG(status) == 2)
            minishell->exit_status = 130;
        else if (WTERMSIG(status) == 3)
        {
            ft_putstr_fd("Quit (core dumped)\n", STDERR_FILENO);
            minishell->exit_status = 131;
        }
    }
    else
        minishell->exit_status = WEXITSTATUS(status);
}