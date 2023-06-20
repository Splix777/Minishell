#include "../include/minishell.h"

int make_command(t_token **head, char *line, int i)
{
    int j;

    j = 0;
    if (is_special_character(line[i]) == FALSE && ft_isspace(line[i]) == FALSE)
    {
        while (is_special_character(line[i + j]) == FALSE && line[i + j] && ft_isspace(line[i + j]) == FALSE)
            j++;
        add_token(head, ft_substr(line, i, j), COMMAND);
    }
    return (j);
}

int make_symbol(t_token **head, char *line, int i)
{
    int j;

    j = 0;
    if (is_special_character(line[i]) == TRUE)
    {
        while (is_special_character(line[i + j]) == TRUE && line[i + j])
        {
            j++;
        }
        add_token(head, ft_substr(line, i, j), SYMBOL);
    }
    return (j);
}

int make_quote(t_token **head, char *line, int i)
{
    int j;

    j = 0;
    if (is_quote(line[i]) == TRUE)
    {
        j++;
        while (line[i + j] && line[i + j] != line[i])
            j++;
        if (line[i + j] == line[i])
            j++;
        if (line[i] == '\"')
            add_token(head, ft_substr(line, i, j), DQUOTE);
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