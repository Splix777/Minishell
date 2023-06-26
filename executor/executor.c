#include "../include/minishell.h"

static int is_builtin(t_minishell *minishell)
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

static void    execute_builtin(t_minishell *minishell)
{
    int     i;

    if (!minishell->command->cmd)
        return ;
    i = 0;
    while (i < 7)
    {
        if (!ft_strcmp(minishell->command->cmd, minishell->builtins->cmd[i]))
            minishell->builtins->func[i](minishell);
        i++;
    }
}

void    executor(t_minishell *minishell)
{
    //pid_t   pid;
    //int     status;

    if (is_builtin(minishell) == TRUE)
        execute_builtin(minishell);
}