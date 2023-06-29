#include "../include/minishell.h"

void ft_free_array(char **array)
{
    int i;

    i = 0;
    if (!array)
        return ;
    if (array != NULL)
    {
        while (array[i] != NULL)
        {
            free(array[i]);
            i++;
        }
        free(array);
    }
}

int line_empty(char *line)
{
    int i;

    i = 0;
    if (!line)
        return (TRUE);
    while (line[i])
    {
        if (line[i] != 32 && (line[i] < 9 || line[i] > 13))
            return (FALSE);
        i++;
    }
    return (TRUE);
}

char    *ft_strjoin_free(char *s1, char *s2)
{
    char    *new_str;

    new_str = ft_strjoin(s1, s2);
    free(s1);
    return (new_str);
}

int ft_arraylen(char **array)
{
    int i;

    i = 0;
    if (!array)
        return (0);
    while (array[i])
        i++;
    return (i);
}