#include "minishell.h"

int main(int argc, char **argv, char **envp)
{
    t_minishell *minishell;
    (void)argc;
    (void)argv;

    minishell = init_structs(envp);

    // Temporary printf to check the env linked list
    int i = 0;
    while (envp[i])
    {
        printf("%s\n", envp[i]);
        i++;
    }
    free_structs(minishell, 5);








    // Display the initial shell prompt
    
    // Enter the main loop for reading and executing commands
    while (1) {
        // Read user input
        
        // Parse the input and construct the command structure
        
        // Handle built-in commands separately
        
        // If not a built-in command, search and launch the executable
        
        // Cleanup any dynamically allocated memory or resources
        
        // Display the prompt for the next command
    }
    
    return (0);
}

