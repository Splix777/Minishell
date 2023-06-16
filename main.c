#include "minishell.h"

void    display_prompt(t_minishell *minishell)
{
    char    *prompt;

    prompt = minishel
}

int main(int argc, char **argv, char **envp)
{
    t_minishell *minishell;
    (void)argc;
    (void)argv;

    minishell = init_structs(envp);
    display_prompt(minishell); // Display the initial shell prompt
}   
    //while (1)
    // Enter the main loop for reading and executing commands

        // Read user input
        
        // Parse the input and construct the command structure
        
        // Handle built-in commands separately
        
        // If not a built-in command, search and launch the executable
        
        // Cleanup any dynamically allocated memory or resources
        
        // Display the prompt for the next command
    
