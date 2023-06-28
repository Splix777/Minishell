#include "../include/minishell.h"

void    ft_echo(t_minishell *minishell)
{
    int i;
    int n;

    i = 0;
    n = 0;
    if (minishell->command->cmd_args == NULL)
    {
        ft_putchar_fd('\n', 1);
        minishell->exit_status = 0;
        return ;
    }
    if (minishell->command->cmd_args[i] && ft_strncmp(minishell->command->cmd_args[i], "-n", 2) == 0)
    {
        n = 1;
        i++;
    }
    while (minishell->command->cmd_args[i])
    {
        ft_putstr_fd(minishell->command->cmd_args[i], 1);
        if (minishell->command->cmd_args[i + 1])
            ft_putchar_fd(' ', 1);
        i++;
    }
    if (n == 0)
        ft_putchar_fd('\n', 1);
    minishell->exit_status = 0;
}