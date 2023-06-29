#include "../include/minishell.h"

int ft_envsize(t_env *env)
{
    int i;
    t_env *tmp;

    i = 0;
    tmp = env;
    while (tmp)
    {
        i++;
        tmp = tmp->next;
    }
    return (i);
}

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
    ft_putstr_fd("minishell: ", STDERR_FILENO);
    ft_putstr_fd(str, STDERR_FILENO);
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

void execute_cmd(t_minishell *minishell, t_command *cmd)
{
    char    **cmd_paths;
    char    **env;
    char    *final_cmd;

    cmd_paths = ft_split(find_env_var(minishell, "PATH"), ':');
    final_cmd = check_cmd(cmd->cmd, cmd_paths);
    env = convert_list_to_array(minishell->env);
    if (final_cmd == NULL)
    {
        free(final_cmd);
        ft_free_array(cmd_paths);
        exit_errors(minishell, "command not found", 127);
    }
    if (execve(final_cmd, cmd->cmd_args, env) < 0)
        perror(final_cmd);
    free(final_cmd);
    ft_free_array(cmd_paths);
    exit(1);
}