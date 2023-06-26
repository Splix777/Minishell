#include "../include/minishell.h"

char    *expand_token(t_minishell *minishell, char *token)
{
    char    *exp_t;
    char    *temp;
    int     i;
    int     j;

    i = 0;
    if (!ft_strchr(token, '$') || !ft_strncmp(token, "$", 2))
		return (token);
    exp_t = ft_strdup("");
    while (token[i])
    {
        j = 0;
        if (token[i] == '$' && token[i + 1] == '?')
        {
            exp_t = ft_strjoin_free(exp_t, ft_itoa(minishell->exit_status));
            i += 2;
        }
        else if (token[i] == '$' && (ft_isalpha(token[i + 1]) || token[i + 1] == '_'))
        {
            i++;
            while (token[i + j] && (ft_isalpha(token[i + j]) || token[i + j] == '_'))
                j++;
            temp = ft_substr(token, i, j);
            exp_t = ft_strjoin_free(exp_t, find_env_var(minishell, temp));
            free(temp);
            i += j;
        }
        else
        {
            temp = ft_substr(token, i, 1);
            exp_t = ft_strjoin_free(exp_t, temp);
            free(temp);
            i++;
        }
    }
    free(token);
    return (exp_t);
}