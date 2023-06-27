#include "../include/minishell.h"

void    set_exit_status(t_minishell *minishell)
{
    if (minishell->command->cmd_args == NULL)
        return ;
    if (ft_atoi(minishell->command->cmd_args[0]) < 0)
    {
        ft_putstr_fd("exit: ", 2);
        ft_putstr_fd(minishell->command->cmd_args[0], 2);
        ft_putstr_fd(": numeric argument required\n", 2);
        minishell->exit_status = 255;
        return ;
    }
    if (minishell->command->cmd_args[1] != NULL)
    {
        ft_putstr_fd("exit: too many arguments\n", 2);
        minishell->exit_status = 1;
    }
    minishell->exit_status = ft_atoi(minishell->command->cmd_args[0]);
}

void    ft_exit(t_minishell *minishell)
{
    int exit_status;

    if (minishell->command)
        set_exit_status(minishell);
    exit_status = minishell->exit_status;
    if (minishell->command != NULL)
        ft_cmdclear(&minishell->command);
    if (minishell->tokens != NULL)
        ft_tokenclear(&minishell->tokens);
    if (minishell->process != NULL)
        free(minishell->process);
    if (minishell->builtins != NULL)
        free(minishell->builtins);
    if (minishell->env != NULL)
        ft_envclear(&minishell->env);
    if (minishell->line != NULL)
        free(minishell->line);
    if (minishell->prompt != NULL)
        free(minishell->prompt); 
    free(minishell);
    printf("exit\n");
    exit(exit_status);
}