#include "../include/minishell.h"

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
        exp = expand_token(minishell, token);
        add_token(head, exp, COMMAND);
    }
    return (j);
}

int make_symbol(t_minishell *minishell, t_token **head, char *line, int i)
{
    int j;
    char *token;
    char *exp;

    j = 1;
    if (is_special_character(line[i]) == TRUE)
    {
        if (is_special_character(line[i + j]) == TRUE && line[i + j] == line[i])
            j++;
        token = ft_substr(line, i, j);
        exp = expand_token(minishell, token);
        add_token(head, exp, SYMBOL);
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
            j++;
        if (line[i] == '\"')
        {
            token = ft_substr(line, i, j);
            exp = expand_token(minishell, token);
            add_token(head, exp, DQUOTE);
        }
        else if (line[i] == '\'')
            add_token(head, ft_substr(line, i, j), SQUOTE);
    }
    return (j);
}

int is_quote(char c)
{
    if (c == '\"' || c == '\'')
        return (TRUE);
    return (FALSE);
}

int is_special_character(char c)
{
    if (c == '|' || c == '<' || c == '>' || c == '\'' || c == '\"')
        return (TRUE);
    return (FALSE);
}