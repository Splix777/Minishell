#include "../include/minishell.h"

void    ft_pwd(t_minishell *minishel)
{
    char    *pwd;

    pwd = getcwd(NULL, 0);
    if (pwd == NULL)
    {
        ft_putstr_fd("pwd: ", 2);
        ft_putstr_fd(strerror(errno), 2);
        ft_putstr_fd("\n", 2);
        minishel->exit_status = 1;
    }
    else
    {
        ft_putstr_fd(pwd, 1);
        ft_putstr_fd("\n", 1);
        free(pwd);
        minishel->exit_status = 0;
    }
}