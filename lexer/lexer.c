#include "../include/minishell.h"

t_token	*tokenize_line(char *line)
{
	int		i;
	t_token	*head;

	i = 0;
	head = NULL;
	while (line[i])
	{
		if (is_special_character(line[i]) == FALSE)
			i += make_command(&head, line, i);
		else if (is_special_character(line[i]) == TRUE && is_quote(line[i]) == FALSE)
			i += make_symbol(&head, line, i);
		else if (is_quote(line[i]) == TRUE)
		{
			i += make_quote(&head, line, i);
			if (line[i] == '\0')
				return (head);
			i++;
		}
		if (ft_isspace(line[i]) == TRUE)
			i++;
	}
    return (head);
}

static void print_tokens(t_token *tokens)
{
	t_token *tmp;

	tmp = tokens;
	while (tmp)
	{
		printf("token: [%s]\n", tmp->token);
		if (tmp->type == 0)
			printf("type: [%s]\n", "QUOTE");
		else if (tmp->type == 1)
			printf("type: [%s]\n", "SYMBOL");
		else if (tmp->type == 2)
			printf("type: [%s]\n", "COMMAND");
		tmp = tmp->next;
	}
}
int	parse_command(t_minishell *minishell, char *line)
{
	minishell->tokens = tokenize_line(line);
	print_tokens(minishell->tokens);
	return (TRUE);
}