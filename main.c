#include "./include/minishell.h"

char	**tokenize_line(t_minishell *minishell, char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{

	}
}

int	parse_command(t_minishell *minishell, char *line)
{
	char	**tokens;

	tokens = tokenize_line(minishell, line);

	return (TRUE);
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
        if (line_empty(line) == FALSE)
        {
            add_history(line);
            if (parse_command(minishell, line))
            {
                
            }
            else
                minishell->exit_status = 1;
        }
        free(line);
        free(prompt);
        prompt = display_prompt(minishell);
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
    
