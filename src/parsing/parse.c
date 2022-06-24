#include "libft.h"
#include "minishell.h"

static char	*next_token(char *input)
{
	char	*next;

	next = ft_strchr(input, ' ') + 1;
	return (next);
}

static int	next_token_i(char *input)
{
	const char	*next = next_token(input);
	if (!next)
		return (-1);
	return (next_token(input) - input);
}


int	parse(char *input)
{
	char	*cursor;
	char	**ag;
	int		next_i;

	ag = NULL;
	(void)ag;
	cursor = input;
	while (*cursor)
	{
		next_i = next_token_i(cursor);
		if (next_i > 0)
			printf("next_token_i : %d\n", next_token_i(cursor));
		else 
			break;
		strs_insert(ft_strndup(cursor, next_token_i(cursor)), &ag);
		cursor = next_token(cursor);
	}
	//DONT FORGET TO FREE ag
	//
	desc_token(ag);
	
	return (0);
}
