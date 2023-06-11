#include "minishell.h"

t_minishell *init_structs(char** envp)
{
    t_minishell *minishell;

    minishell = malloc(sizeof(t_minishell));
    if (!minishell)
        return (NULL);
    memset(minishell, 0, sizeof(t_minishell));
    minishell->t_command = init_command();
    if (minishell->t_command == NULL)
        free_structs(minishell, 1);
    minishell->t_history = init_history();
    if (minishell->t_history == NULL)
        free_structs(minishell, 2);
    minishell->t_process = init_process();
    if (minishell->t_process == NULL)
        free_structs(minishell, 3);
    if (!envp)
        minishell->t_env_variable = create_env_node();
    else
        minishell->t_env_variable = init_env(envp);
    if (minishell->t_env_variable == NULL)
        free_structs(minishell, 4);
    return (minishell);
}

t_command   *init_command(void)
{
    t_command   *command;

    command = malloc(sizeof(t_command));
    if (!command)
        return (NULL);
    command->cmd = NULL;
    command->cmd_args = NULL;
    command->input_redirection = NULL;
    command->output_redirection = NULL;
    command->append_mode = 0;
    command->here_doc = 0;
    command->here_doc_delimiter = NULL;
    command->here_document_lines = NULL;
    command->background_execution = 0;
    return (command);
}

t_history   *init_history(void)
{
    t_history *history;
    
    history = malloc(sizeof(t_history));
    if (!history) 
        return (NULL);
    history->command = NULL;
    history->timestamp = 0;
    history->next = NULL;
    return (history);
}

t_env_variable  *init_env(char **envp)
{
    t_env_variable  *head;
    t_env_variable  *node;
    char            *name;
    char            *value;

    while (*envp != NULL)
    {
        name = ft_strdup(*envp);
        value = ft_strchr(name, '=');
        if (value != NULL)
        {
            *value = '\0';
            value++;
            node = create_env_node(name, value);
            if (!node)
            {
                ft_lstclear(&head, free);
                return (NULL);
            }
            ft_lstadd_back(&head, node);
        }
        free(name);
        envp++;
    }
    return (head);
}

t_process *init_process(void)
{
    t_process *process;
    
    process = malloc(sizeof(t_process));
    if (!process)
        return (NULL);
    process->pid = 0;
    process->status = 0;
    process->command = NULL;
    process->next = NULL;
    return (process);
}
