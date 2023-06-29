#include "../include/minishell.h"

char    **convert_list_to_array(t_env *list)
{
    char    **array;
    int     i;

    i = 0;
    array = malloc(sizeof(char *) * (ft_envsize(list) + 1));
    if (!array)
        return (NULL);
    while (list)
    {
        array[i] = ft_strjoin(list->name, "=");
        array[i] = ft_strjoin_free(array[i], list->value);
        list = list->next;
        i++;
    }
    array[i] = NULL;
    return (array);
}

void    exit_errors(t_minishell *minishell, char *str, int code)
{
    ft_putstr_fd(str, STDERR_FILENO);
    ft_putstr_fd(": command not found", STDERR_FILENO);
    ft_putstr_fd("\n", STDERR_FILENO);
    minishell->exit_status = code;
    exit(code);
}

char    *check_cmd(char *cm, char **paths)
{
    char    *tmp;
    char    *final_cmd;

    if (cm[0] == '/' || !ft_strncmp("../", cm, 3) || !ft_strncmp("./", cm, 2))
        return (cm);
    if (paths == NULL)
        return (NULL);
    while (*paths)
    {
		tmp = ft_strjoin(*paths, "/");
		final_cmd = ft_strjoin(tmp, cm);
		free(tmp);
		if (access(final_cmd, F_OK | X_OK) == 0)
			return (final_cmd);
		free(final_cmd);
		paths++;
	}
	return (NULL);
}

char    **add_cmd_to_args(char *cmd, char **args)
{
    char    **new_args;
    int     i;

    i = 0;
    if (!args)
        return (NULL);
    new_args = malloc(sizeof(char *) * (ft_arraylen(args) + 2));
    if (!new_args)
        return (NULL);
    new_args[i] = ft_strdup(cmd);
    while (args[i])
    {
        new_args[i + 1] = ft_strdup(args[i]);
        i++;
    }
    new_args[i + 1] = NULL;
    ft_free_array(args);
    return (new_args);
}

void execute_cmd(t_minishell *minishell, t_command *cmd)
{
    char    **full_args;
    char    **cmd_paths;
    char    **env;
    char    *final_cmd;

    cmd_paths = ft_split(find_env_var(minishell, "PATH"), ':');
    final_cmd = check_cmd(cmd->cmd, cmd_paths);
    full_args = add_cmd_to_args(cmd->cmd, cmd->cmd_args);
    env = convert_list_to_array(minishell->env);
    if (final_cmd == NULL)
    {
        free(final_cmd);
        ft_free_array(cmd_paths);
        ft_free_array(full_args);
        exit_errors(minishell, cmd->cmd, 127);
    }
    if (execve(final_cmd, full_args, env) < 0)
        perror(final_cmd);
    free(final_cmd);
    ft_free_array(cmd_paths);
    ft_free_array(full_args);
    exit(1);
}