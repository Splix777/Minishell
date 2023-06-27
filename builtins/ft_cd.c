#include "../include/minishell.h"

static int	change_dir(t_minishell *minishell, char *dir)
{
	char	pwd[MAX_PATH];
	char	*oldpwd;
	char 	*tmp;
	t_env	*env;

	oldpwd = ft_strdup(find_env_var(minishell, "PWD"));
	if (chdir(dir) == -1)
		return (perror(dir), -1);
	env = find_env_var_node(minishell, "OLDPWD");
	if (env)
	{
		free(env->value);
		env->value = oldpwd;
	}
	else 
		ft_add_env_node(&minishell->env, ft_strdup("OLDPWD"), oldpwd);
	if (getcwd(pwd, sizeof(pwd)) == NULL)
		pwd[0] = '\0';
	tmp = ft_strdup(pwd);
	env = find_env_var_node(minishell, "PWD");
	if (env)
	{
		free(env->value);
		env->value = tmp;
	}
	else
		ft_add_env_node(&minishell->env, ft_strdup("PWD"), tmp);
	return (0);
}

static void	go_home(t_minishell *minishell)
{
	char	*home;

	home = find_env_var(minishell, "HOME");
	if (!home)
	{
		ft_putstr_fd("cd: HOME not set\n", 2);
		return ;
	}
	change_dir(minishell, home);
}

static void	expand_home(t_minishell *minishell, char *path)
{
	char	*home;
	char	*res;
	char	*tmp;

	home = find_env_var(minishell, "HOME");
	if (!home)
		return (ft_putendl_fd("cd: HOME not set", 2));
	res = ft_strjoin(home, "/");
	tmp = res;
	res = ft_strjoin(res, path + 1);
	free(tmp);
	if (chdir(res) == -1)
		perror(res);
}

void	ft_cd(t_minishell *minishell)
{
	if (!minishell->command->cmd_args)
		return (go_home(minishell));
	if (minishell->command->cmd_args[1] != NULL)
		return (ft_putstr_fd("cd: too many arguments\n", 2));
	if (ft_strncmp(minishell->command->cmd_args[0], "~", 2) == 0)
		return (expand_home(minishell, minishell->command->cmd_args[0]));
	if (change_dir(minishell, minishell->command->cmd_args[0]) == -1)
		minishell->exit_status = 1;
	else
		minishell->exit_status = 0;
}