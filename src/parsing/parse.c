#include "libft.h"
#include "minishell.h"

static char	*next_token(char *input)
{
	char	*next;

	next = ft_strchr(input, ' ');
	if (!next)
		return (NULL);
	return (next + 1);
}
/*
static int	next_token_i(char *input)
{
	const char	*next = next_token(input);
	if (!next)
		return (-1);
	return (next_token(input) - input);
}
*/

static int	end_token_i(char *input)
{
	char	*end = ft_strchr(input, ' ');
	if (!end)
		end = ft_strchr(input, '\0');
	end -= 1;
	return (end - input);
}

/*
static int	end_token_i(char *input)
{
	int	i;

	i = -1;
	while (input[++i])
	{
		if ()
	}
}
*/
int	parse(char *input)
{
	char	*cursor;
	char	**ag;
	int		end_i;

	ag = NULL;
	(void)ag;
	cursor = input;
	while (cursor && *cursor)
	{
		printf("len : %d\n", strs_len(ag));
		end_i = end_token_i(cursor);
		strs_insert(&ag, ft_strndup(cursor, end_i + 1));
		cursor = next_token(cursor);
	}
	//DONT FORGET TO FREE ag
	desc_token(ag);
	return (0);
}
