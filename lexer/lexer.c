#include "../include/minishell.h"

t_token	*tokenize_line(t_minishell *minishell, char *line)
{
	int		i;
	t_token	*head;

	i = 0;
	head = NULL;
	while (line[i])
	{
		if (is_special_character(line[i]) == FALSE && !is_quote(line[i]))
			i += make_command(minishell, &head, line, i);
		else if (is_special_character(line[i]) == TRUE && is_quote(line[i]) == FALSE)
			i += make_symbol(minishell, &head, line, i);
		else if (is_quote(line[i]) == TRUE)
		{
			i += make_quote(minishell, &head, line, i);
			if (line[i] == '\0')
				return (head);
			i++;
		}
		if (ft_isspace(line[i]) == TRUE)
			i++;
	}
    return (head);
}

void print_tokens(t_token *tokens)
{
	t_token *tmp;

	tmp = tokens;
	while (tmp)
	{
		printf("token: [%s]\n", tmp->token);
		if (tmp->type == 0)
			printf("type: [%s]\n", "SQUOTE");
		if (tmp->type == 1)
			printf("type: [%s]\n", "DQUOTE");
		if (tmp->type == 2)
			printf("type: [%s]\n", "SYMBOL");
		if (tmp->type == 3)
			printf("type: [%s]\n", "COMMAND");
		if (tmp->type == 4)
			printf("type: [%s]\n", "PIPE");
		if (tmp->type == 5)
			printf("type: [%s]\n", "REDERICT");
		if (tmp->type == 6)
			printf("type: [%s]\n", "REDIR_IN");
		if (tmp->type == 7)
			printf("type: [%s]\n", "REDIR_OUT");
		if (tmp->type == 8)
			printf("type: [%s]\n", "APPEND");
		if (tmp->type == 9)
			printf("type: [%s]\n", "HEREDOC");
		if (tmp->type == 10)
			printf("type: [%s]\n", "HEREDOC_DELIM");
		if (tmp->type == 11)
			printf("type: [%s]\n", "COMMAND_ARG");
		if (tmp->type == 12)
			printf("type: [%s]\n", "FILE");
		tmp = tmp->next;
	}
}

void	type_redir(t_token *token)
{
	if (!ft_strncmp(token->token, "<<", 3))
	{
		token->type = HEREDOC;
		token->next->type = HEREDOC_DELIM;
	}
	else if (!ft_strncmp(token->token, "<", 2))
	{
		token->type = REDIR_IN;
		token->next->type = FILE;
	}
	else if (!ft_strncmp(token->token, ">", 2))
	{
		token->type = REDIR_OUT;
		token->next->type = FILE;
	}
	else if (!ft_strncmp(token->token, ">>", 3))
	{
		token->type = APPEND;
		token->next->type = FILE;
	}
}

static void	label_tokens(t_token *tokens)
{
	t_token	*tmp;

	tmp = tokens;
	while (tmp && tmp->next)
	{
		if (tmp->type == COMMAND && tmp->next->type == COMMAND)
			tmp->next->type = COMMAND_ARG;
		if (tmp->type == COMMAND_ARG && tmp->next->type == COMMAND)
			tmp->next->type = COMMAND_ARG;
		if (tmp->type == REDIRECT && tmp->next->type == COMMAND)
			type_redir(tmp);
		tmp = tmp->next;
	}
}

int	parse_command(t_minishell *minishell)
{
	minishell->tokens = tokenize_line(minishell, minishell->line);
	if (parse_errors(minishell) == FALSE)
		return (FALSE);
	label_tokens(minishell->tokens);
	return (TRUE);
	print_tokens(minishell->tokens);
}