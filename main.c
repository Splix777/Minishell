#include "./include/minishell.h"

char    *find_env_var(t_minishell *minishell, char *var)
{
    t_env   *env;

    env = minishell->env;
    while (env)
    {
        if (ft_strncmp(env->name, var, ft_strlen(var)) == 0)
            return (env->value);
        env = env->next;
    }
    return (NULL);
}

char    *display_prompt(t_minishell *minishell)
{
    char    *prompt;
    char    *user;
    char    *pwd;

    user = find_env_var(minishell, "USER");
    if (!user)
        user = ft_strdup("guest");
    user = ft_strjoin(user, "@minishell: ");
    pwd = find_env_var(minishell, "PWD");
    pwd = ft_strjoin(pwd, "$ ");
    prompt = ft_strjoin(user, pwd);
    free(pwd);
    free(user);
    return (prompt);
}

int main(int argc, char **argv, char **envp)
{
    t_minishell *minishell;
    char        *line;
    char        *prompt;
    (void)argc;
    (void)argv;

    minishell = init_structs(envp);
    prompt = display_prompt(minishell);
    line = readline(prompt);
    // while (line)
    // {
    //     // Display the initial shell prompt
    // }
    free(line);
    free(prompt);
    free_structs(minishell);
    return (0);
}
 

    // Enter the main loop for reading and executing commands

        // Read user input
        
        // Parse the input and construct the command structure
        
        // Handle built-in commands separately
        
        // If not a built-in command, search and launch the executable
        
        // Cleanup any dynamically allocated memory or resources
        
        // Display the prompt for the next command
    
