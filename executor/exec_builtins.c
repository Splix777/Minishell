#include "../include/minishell.h"

int is_builtin(t_minishell *minishell)
{
    int     i;
    char    *str;

    if (!minishell->command->cmd)
        return (FALSE);
    i = 0;
    while (i < 7)
    {
        str = minishell->builtins->cmd[i];
        if (!ft_strncmp(minishell->command->cmd, str, ft_strlen(str)))
            return (TRUE);
        i++;
    }
    return (FALSE);
}

void    execute_builtin(t_minishell *minishell)
{
    int     i;
    int     tmpin;
    int     tmpout;

    if (!minishell->command->cmd)
        return ;
    i = 0;
    tmpin = dup(STDIN_FILENO);
    tmpout = dup(STDOUT_FILENO);
    open_fds(minishell, minishell->command);
    if (minishell->command->fdin != STDIN_FILENO)
    {
        dup2(minishell->command->fdin, STDIN_FILENO);
        close(minishell->command->fdin);
    }
    if (minishell->command->fdout != STDOUT_FILENO)
    {
        dup2(minishell->command->fdout, STDOUT_FILENO);
        close(minishell->command->fdout);
    }
    while (i < 7)
    {
        if (!ft_strcmp(minishell->command->cmd, minishell->builtins->cmd[i]))
            minishell->builtins->func[i](minishell);
        i++;
    }
    dup2(tmpin, STDIN_FILENO);
    dup2(tmpout, STDOUT_FILENO);
    close(tmpin);
    close(tmpout);
}