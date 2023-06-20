#include "../include/minishell.h"

void	ft_cd(t_minishell *minishell)
{
	char *path;
	t_env *env;

	path = NULL;
    env =  NULL;
	if (minishell->tokens->next)
	{
		path = minishell->tokens->next->token;
	}
	if (path == NULL)
		path = find_env_var(minishell, "HOME");
	if (path == NULL)
	{
		ft_putendl_fd("cd: HOME not set", STDERR_FILENO);
		minishell->exit_status = 1;
	}
	else if (chdir(path) == -1)
	{
		ft_putstr_fd("cd: ", STDERR_FILENO);
		ft_putstr_fd(path, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
		minishell->exit_status = 1;
	}
	else
	{
		env = find_env_var_node(minishell, "OLDPWD");
		if (env)
			free(env->value);
		env->value = ft_strdup(find_env_var(minishell, "PWD"));
		env = find_env_var_node(minishell, "PWD");
		if (env)
			free(env->value);
		env->value = getcwd(NULL, 0);
		minishell->exit_status = 0;
	}
}