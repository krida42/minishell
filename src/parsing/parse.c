#include "minishell.h"

static int	next_token(char *input)
{
	(void) input;
	return (0);
}

int	parse(char *input)
{
	char	*cursor;

	cursor = input;
	while (next_token(cursor))
		cursor = ft_strchr(input, ' ') + 1;
	return (0);
}
