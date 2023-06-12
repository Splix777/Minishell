#include "minishell.h"

t_minishell *init_structs(char** envp)
{
    t_minishell *minishell;

    minishell = malloc(sizeof(t_minishell));
    if (!minishell)
        return (NULL);
    memset(minishell, 0, sizeof(t_minishell));
    minishell->command = init_command();
    if (minishell->command == NULL)
        free_structs(minishell, 1);
    minishell->history = init_history();
    if (minishell->history == NULL)
        free_structs(minishell, 2);
    minishell->process = init_process();
    if (minishell->process == NULL)
        free_structs(minishell, 3);
    if (!envp)
        minishell->env = create_default_env();
    else
        minishell->env = init_env(envp);
    if (minishell->env == NULL)
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
    t_env_variable  *env;

    env = malloc(sizeof(t_env_variable));
    if (!env)
        return (NULL);
    env->envp = envp;
    env->path = find_path(envp);
    env->pwd = find_pwd(envp);
    env->oldpwd = NULL;
    env->shlvl = find_shlvl(envp);
    env->underscore = find_underscore(envp);
    return (env);
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
