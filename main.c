#include "./include/minishell.h"

void valgrind(void)
{
    system("leaks minishell");
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

                // ft_cd(minishell);
                // ft_env(minishell);
                // ft_pwd(minishell);
                // ft_exit(minishell);
                // ft_echo(minishell);
                // ft_export(minishell);
                // ft_unset(minishell);

            }
            else
                minishell->exit_status = 1;
        }
        ft_tokenclear(&minishell->tokens);
        free(minishell->line);
        free(minishell->prompt);
        minishell->prompt = display_prompt(minishell);
        minishell->line = readline(minishell->prompt);
    }
    ft_exit(minishell);
}

        // Parse the input and construct the command structure
        
        // Handle built-in commands separately
        
        // If not a built-in command, search and launch the executable
        
        // Cleanup any dynamically allocated memory or resources
        
        // Display the prompt for the next command
    
