#include "minishell.h"

static t_token	*new_token(char *value, t_toktype type)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	token->value = value;
	token->type = type;
	token->prev = NULL;
	token->next = NULL;
	return (token);
}

t_token	*get_first(t_token *token)
{
	while (token->prev)
		token = token->prev;
	return (token);
}

t_token	*get_last(t_token *token)
{
	while (token->next)
		token = token->next;
	return (token);
}

void	add_back(t_token **token, char *value, t_toktype type)
{
	t_token	*last;

	if (!*token)
	{
		*token = new_token(value, type);
		return ;
	}
	last = get_last(*token);
	last->next = new_token(value, type);
	(last->next)->prev = last;
}

int	token_size(t_token *token)
{
	int	i;

	i = 0;
	while (token)
	{
		token = token->next;
		i++;
	}
	return (i);
}
