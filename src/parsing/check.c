#include "minishell.h"

void	set_quote_state(char c, int *squote, int *dquote)
{
	if (c == '\'' && !*dquote)
		*squote = !*squote;
	else if (c == '"' && !*squote)
		*dquote = !*dquote;
}

int	check_special(char *input)
{
	int	squote;
	int	dquote;

	squote = 0;
	dquote = 0;
	while (*input)
	{
		set_quote_state(*input, &squote, &dquote);
		if (*input == '\\')
			return (1);
		if (*input == ';' && !(squote || dquote))
			return (1);
		input++;
	}
	return (0);
}

int	check_unclosed(char *input)
{
	int	squote;
	int	dquote;

	squote = 0;
	dquote = 0;
	while (*input)
	{
		set_quote_state(*input, &squote, &dquote);
		input++;
	}
	return (squote || dquote);
}
