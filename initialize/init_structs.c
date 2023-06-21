#include "../include/minishell.h"

t_minishell *init_structs(char** envp)
{
    t_minishell *minishell;

    minishell = malloc(sizeof(t_minishell));
    if (!minishell)
        return (NULL);
    memset(minishell, 0, sizeof(t_minishell));
    minishell->command = init_command();
    if (minishell->command == NULL)
        free_structs(minishell);
    minishell->process = init_process();
    if (minishell->process == NULL)
        free_structs(minishell);
    minishell->builtins = init_builtins();
    if (minishell->builtins == NULL)
        free_structs(minishell);
    minishell->env = init_env(envp);
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
    command->append_mode = FALSE;
    command->here_doc = FALSE;
    command->here_doc_delimiter = NULL;
    return (command);
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

t_env  *init_env(char **envp)
{
    t_env   *head;
    t_env   *env;
    int     i;

    head = NULL;
    i = 0;
    if (!envp)
        return (head);
    while (envp[i])
    {
        env = malloc(sizeof(t_env));
        if (!env)
        {
            ft_envclear(&head);
            return (NULL);
        }
        env->name = ft_substr(envp[i], 0, (ft_strchr(envp[i], '=') - envp[i]) + 1);
        env->value = ft_strdup(ft_strchr(envp[i], '=') + 1);
        env->next = NULL;
        add_env(&head, env);
        i++;
    }
    return (head);
}

t_builtins  *init_builtins(void)
{
    t_builtins  *builtins;

    builtins = malloc(sizeof(t_builtins));
    if (!builtins)
        return (NULL);
    builtins->cmd[0] = "echo";
    builtins->func[0] = &ft_echo;
    builtins->cmd[1] = "cd";
    builtins->func[1] = &ft_cd;
    builtins->cmd[2] = "pwd";
    builtins->func[2] = &ft_pwd;
    builtins->cmd[3] = "export";
    builtins->func[3] = &ft_export;
    builtins->cmd[4] = "unset";
    builtins->func[4] = &ft_unset;
    builtins->cmd[5] = "env";
    builtins->func[5] = &ft_env;
    builtins->cmd[6] = "exit";
    builtins->func[6] = &ft_exit;
    return (builtins);
}

