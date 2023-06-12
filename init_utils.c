#include "minishell.h"

char    *find_path(char **envp)
{
	while (*envp && ft_strncmp("PATH=", *envp, 5))
		envp++;
	if (*envp == NULL)
		return (NULL);
	return (*envp + 5);
}

char    *find_pwd(char **envp)
{
    while (*envp && ft_strncmp("PWD=", *envp, 4))
        envp++;
    if (*envp == NULL)
        return (NULL);
    return (*envp + 4);
}

char    *find_shlvl(char **envp)
{
    while (*envp && ft_strncmp("SHLVL=", *envp, 6))
        envp++;
    if (*envp == NULL)
        return (NULL);
    return (*envp + 6);
}

char    *find_underscore(char **envp)
{
    while (*envp && ft_strncmp("_=", *envp, 2))
        envp++;
    if (*envp == NULL)
        return (NULL);
    return (*envp + 2);
}

t_env_variable  *create_default_env(void)
{
    t_env_variable  *env;

    env = malloc(sizeof(t_env_variable));
    if (!env)
        return (NULL);
    env->envp = NULL;
    env->path = PATH;
    env->pwd = PWD_PATH;
    env->oldpwd = NULL;
    env->shlvl = SHLVL;
    env->underscore = UNDERSCORE;
    return (env);
}