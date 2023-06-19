#include "../include/minishell.h"

char *ft_strcat(char *dest, const char *src)
{
    size_t dest_len;
    size_t i;
    
    i = 0;
    dest_len = ft_strlen(dest);
    while (src[i] != '\0') {
        dest[dest_len + i] = src[i];
        i++;
    }
    dest[dest_len + i] = '\0';
    return (dest);
}

char *multi_strjoin(int total_len, int count, ...)
{
    va_list strings;
    char    *joined;
    char    *str;

    va_start (strings, count);
    joined = malloc((total_len + 1) * sizeof(char));
    if (!joined) 
    {
        va_end (strings);
        return NULL;
    }
    joined[0] = '\0';
    while (count > 0) {
        str = va_arg(strings, char*);
        ft_strcat(joined, str);
        count--;
    }
    va_end (strings);
    return (joined);
}

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

t_env   *find_env_var_node(t_minishell *minishell, char *var)
{
    t_env   *env;

    env = minishell->env;
    while (env)
    {
        if (ft_strncmp(env->name, var, ft_strlen(var)) == 0)
            return (env);
        env = env->next;
    }
    return (NULL);
}

char    *display_prompt(t_minishell *minishell)
{
    char    *prompt;
    char    *user;
    char    pwd[MAX_PATH];
    int     total_len;

    total_len = 0;
    total_len += ft_strlen(COLOR_BLUE);
    total_len += ft_strlen(COLOR_GREEN);
    total_len += ft_strlen(RESET);
    total_len += ft_strlen("@minishell: "); 
    total_len += ft_strlen("$ ");
    user = find_env_var(minishell, "USER");
    if (!user)
        user = "guest";
    if (getcwd(pwd, sizeof(pwd)) == NULL)
        pwd[0] = '\0';
    total_len += ft_strlen(user);
    total_len += ft_strlen(pwd);
    prompt = multi_strjoin(total_len, 8, COLOR_BLUE, user, "@minishell: ", COLOR_GREEN, pwd, "$ ", RESET, "\0");
    return (prompt);
}