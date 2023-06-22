#include "../include/minishell.h"

void ft_free_array(char **array)
{
    int i;

    i = 0;
    if (array)
    {
        while (array[i])
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