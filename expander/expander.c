#include "../include/minishell.h"

char    *ft_strjoin_free(char *s1, char *s2)
{
    char    *new_str;

    new_str = ft_strjoin(s1, s2);
    free(s1);
    return (new_str);
}

char    *expand_token(t_minishell *minishell, char *token)
{
    char    *expanded_token;
    char    *temp;
    int     i;
    int     j;

    i = 0;
    if (!ft_strchr(token, '$') || !ft_strncmp(token, "$", 2))
		return (token);
    expanded_token = ft_strdup("");
    while (token[i])
    {
        j = 0;
        if (token[i] == '$' && token[i + 1] == '?')
        {
            expanded_token = ft_strjoin_free(expanded_token, ft_itoa(minishell->exit_status));
            i += 2;
        }
        else if (token[i] == '$' && (ft_isalpha(token[i + 1]) || token[i + 1] == '_'))
        {
            i++;
            while (token[i + j] && (ft_isalpha(token[i + 1]) || token[i + 1] == '_'))
                j++;
            temp = ft_substr(token, i, j);
            expanded_token = ft_strjoin_free(expanded_token, find_env_var(minishell, temp));
            free(temp);
            i += j;
        }
        else
        {
            temp = ft_substr(token, i, 1);
            expanded_token = ft_strjoin_free(expanded_token, temp);
            free(temp);
            i++;
        }
    }
    free(token);
    return (expanded_token);
}