#include "./include/minishell.h"

// void valgrind(void)
// {
//     system("leaks minishell");
// }

int check_valid_shlvl(int shlvl_int)
{
    if (shlvl_int < 0)
        shlvl_int = 0;
    if (shlvl_int >= 999)
    {
        ft_putstr_fd("shell level (1000) too high, resetting to 1\n", 2);
        shlvl_int = 1;
    }
    return (shlvl_int);
}

void set_shlvl(t_minishell *minishell)
{
    char    *shlvl;
    int     shlvl_int;
    t_env   *env;

    shlvl = find_env_var(minishell, "SHLVL");
    if (shlvl == NULL)
        shlvl_int = 1;
    else
        shlvl_int = ft_atoi(shlvl) + 1;
    shlvl_int = check_valid_shlvl(shlvl_int);
    env = find_env_var_node(minishell, "SHLVL");
    if (env)
    {
        free(env->value);
        env->value = ft_itoa(shlvl_int);
    }
    else
        ft_add_env_node(&minishell->env, "SHLVL", ft_itoa(shlvl_int));
}

void reset_loop(t_minishell *minishell)
{
    ft_cmdclear(&minishell->command);
    ft_tokenclear(&minishell->tokens);
    free(minishell->line);
    free(minishell->prompt);
    minishell->prompt = display_prompt(minishell);
    minishell->line = readline(minishell->prompt);
}

int main(int argc, char **argv, char **envp)
{
    t_minishell *minishell;
    (void)      argc;
    (void)      argv;

    //atexit(valgrind);
    minishell = init_structs(envp);
    minishell->prompt = display_prompt(minishell);
    minishell->line = readline(minishell->prompt);
    set_shlvl(minishell);
    while (minishell->line)
    {
        listen_signals();
        if (line_empty(minishell->line) == FALSE)
        {
            add_history(minishell->line);
            if (parse_command(minishell) == TRUE)
            {
                build_command_structs(minishell);
                executor(minishell);
            }
        }
        reset_loop(minishell);
    }
    clear_history();
    ft_exit(minishell);
}       

    
