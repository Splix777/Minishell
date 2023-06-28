#include "../include/minishell.h"

int do_heredoc(t_minishell *minishell, char *delimiter)
{
    int     fd;
    char    *line;
    (void) minishell;

    fd = open("/tmp/heredoc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
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
            ft_putendl_fd(line, fd);
            free(line);
            ft_putstr_fd("heredoc> ", STDIN_FILENO);
            line = get_next_line(STDIN_FILENO);
        }
        free(line);
    }
    free(delimiter);
    return (fd);
}

int open_heredoc(t_minishell *minishell, char *delimiter)
{
    int fd;

    printf("HERE\n");
    minishell->process->pid = fork();
    fd = 0;
    if (minishell->process->pid == 0)
    {
        fd = do_heredoc(minishell, delimiter);
        exit(0);
    }
    else if (minishell->process->pid < 0)
        ft_putendl_fd("Error: Fork failed", 2);
    else
        waitpid(minishell->process->pid, &minishell->process->status, 0);
    minishell->exit_status = WEXITSTATUS(minishell->process->status);
    return (fd);
}