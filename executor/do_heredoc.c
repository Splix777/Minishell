#include "../include/minishell.h"

void do_heredoc(t_minishell *minishell, char *delimiter)
{
    int     fd;
    char    *line;
    char    *tmp;

    fd = open("/tmp/.heredoc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    delimiter = ft_strjoin_free(delimiter, "\n");
    if (fd < 0)
        ft_putendl_fd("Error: Failed to open heredoc file", 2);
    else
    {
        ft_putstr_fd("heredoc> ", STDIN_FILENO);
        line = get_next_line(STDIN_FILENO);
        while (line)
        {
            if (!ft_strcmp(line, delimiter))
                break ;
            tmp = expand_token(minishell, line);
            ft_putendl_fd(tmp, fd);
            free(tmp);
            ft_putstr_fd("heredoc> ", STDIN_FILENO);
            line = get_next_line(STDIN_FILENO);
        }
        free(line);
    }
    free(delimiter);
    close(fd);
}

int open_heredoc(t_minishell *minishell, char *delimiter)
{
    int fd;
    pid_t pid;
    int status;

    pid = make_fork();
    fd = 0;
    if (pid == 0)
    {
        do_heredoc(minishell, delimiter);
        exit(0);
    }
    else
        waitpid(pid, &status, 0);
    minishell->exit_status = WEXITSTATUS(status);
    fd = open("/tmp/.heredoc", O_RDONLY);
    return (fd);
}