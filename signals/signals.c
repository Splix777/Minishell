#include "../include/minishell.h"

void    sigint_handler(int sig)
{
    (void)sig;
    write(1, "\n", 1);
    rl_on_new_line();
    //rl_replace_line("", 0);
    rl_redisplay();
}

void    sigquit_handler(int sig)
{
    (void)sig;
    close (STDIN_FILENO);
}

void    listen_signals(void)
{
    signal(SIGQUIT, &sigquit_handler);
    signal(SIGINT, &sigint_handler);
}