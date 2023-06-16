#include "./include/minishell.h"

static int line_is_empty(char *line)
{
    int i;

    i = 0;
    if (!line)
        return (1);
    while (line[i])
    {
        if (line[i] != 32 && (line[i] >= 9 && line[i] <= 13))
            return (0);
        i++;
    }
    return (1);
}

int main(int argc, char **argv, char **envp)
{
    t_minishell *minishell;
    char        *line;
    char        *prompt;
    (void)      argc;
    (void)      argv;

    minishell = init_structs(envp);
    prompt = display_prompt(minishell);
    line = readline(prompt);
    while (line)
    {
        listen_signals();
        if (!line_is_empty(line))
        {

        }
        free(line);
        line = readline(prompt);
    }
    free(prompt);
    free(line);
    free_structs(minishell);
}

        // Read user input
        
        // Parse the input and construct the command structure
        
        // Handle built-in commands separately
        
        // If not a built-in command, search and launch the executable
        
        // Cleanup any dynamically allocated memory or resources
        
        // Display the prompt for the next command
    
