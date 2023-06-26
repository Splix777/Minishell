#include "./include/minishell.h"

void valgrind(void)
{
    system("leaks minishell");
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

    atexit(valgrind);
    minishell = init_structs(envp);
    minishell->prompt = display_prompt(minishell);
    minishell->line = readline(minishell->prompt);
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
    rl_clear_history();
    ft_exit(minishell);
}       
        // Handle built-in commands separately
        
        // If not a built-in command, search and launch the executable

    
