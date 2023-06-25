#include "../include/minishell.h"

static char    *remove_quotes(char *token)
{
    int i;
    int j;
    char *new_token;

    i = 0;
    j = 0;
    while (token[i + j])
    {
        if (token[i] == '\'' || token[i] == '\"')
            i++;
        j++;
    }
    new_token =  malloc(sizeof(char) * (j + 1));
    i = -1;
    j = 0;
    while (token[++i])
    {
        while (token[i] == '\'' || token[i] == '\"')
            i++;
        new_token[j] = token[i];
        j++;
    }
    new_token[i] = '\0';
    free(token);
    return (new_token);
}

static void remove_spaces(t_minishell *minishell, t_token **head, char *exp)
{
    char    **temp;
    int     i;

    i = 0;
    temp = ft_split(exp, ' ');
    while (temp[i])
    {
        make_command(minishell, head, temp[i], 0);
        i++;
    }
    ft_free_array(temp);
    free(exp);
}

int make_command(t_minishell *minishell, t_token **head, char *line, int i)
{
    int     j;
    char    *token;
    char    *exp;

    j = 0;
    if (is_special_character(line[i]) == FALSE && ft_isspace(line[i]) == FALSE)
    {
        while (is_special_character(line[i + j]) == FALSE && line[i + j] && ft_isspace(line[i + j]) == FALSE)
            j++;
        token = ft_substr(line, i, j);
        token = remove_quotes(token);
        exp = expand_token(minishell, token);
        if (ft_strchr(exp, ' ') != NULL)
            remove_spaces(minishell, head, exp);
        else
            add_token(head, exp, COMMAND);
    }
    return (j);
}

int make_symbol(t_minishell *minishell, t_token **head, char *line, int i)
{
    int j;
    char *token;
    //char *exp;
    (void)minishell;

    j = 1;
    if (is_special_character(line[i]) == TRUE)
    {
        if (is_special_character(line[i + j]) == TRUE && line[i + j] == line[i] && line[i] != '|')
            j++;
        token = ft_substr(line, i, j);
        // exp = expand_token(minishell, token);
        if (line[i] == '|')
            add_token(head, token, PIPE);
        else if (line[i] == '<')
            add_token(head, token, REDIRECT);
        else if (line[i] == '>')
            add_token(head, token, REDIRECT);
        //add_token(head, exp, SYMBOL);
    }
    return (j);
}

int make_quote(t_minishell *minishell, t_token **head, char *line, int i)
{
    int j;
    char *token;
    char *exp;

    j = 0;
    if (is_quote(line[i]) == TRUE)
    {
        j++;
        while (line[i + j] && line[i + j] != line[i])
            j++;
        if (line[i + j] == line[i])
            j--;
        if (line[i] == '\"')
        {
            token = ft_substr(line, i + 1, j);
            exp = expand_token(minishell, token);
            add_token(head, exp, COMMAND);
        }
        else if (line[i] == '\'')
            add_token(head, ft_substr(line, i + 1, j), COMMAND);
    }
    return (j + 1);
}

