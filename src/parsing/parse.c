#include "libft.h"
#include "minishell.h"

/*
static char	*next_token0(char *input)
{
	char	*next;

	next = ft_strchr(input, ' ');
	if (!next)
		return (NULL);
	return (next + 1);
}
*/
/*
   static int	next_token_i(char *input)
   {
   const char	*next = next_token(input);
   if (!next)
   return (-1);
   return (next_token(input) - input);
   }
   */
/*
   static int	end_token_i0(char *input)
   {
   char	*end = ft_strchr(input, ' ');
   if (!end)
   end = ft_strchr(input, '\0');
   end -= 1;
   return (end - input);
   }
   */
static char	*next_token(char *input)
{
	int	i;

	i = -1;
	while (input[++i])
		if (isinset(input[i], "<>| "))
			break;
	while (input[i])
	{

	}
	return input;
}

static int	end_token_i(char *input)
{
	int	i;

	i = -1;
	while (input[++i])
		if (isinset(input[i], "<>| "))
			return (i - 1);
	return (i - 1);
}


int	parse(char *input)
{
	char	*cursor;
	char	**ag;
	char	*token;

	ag = NULL;
	(void)ag;
	cursor = input;
	while (cursor && *cursor)
	{
		token = ft_strndup(cursor, end_token_i(cursor) + 1);
		strs_insert(&ag, token);
		free(token);
		cursor = next_token(cursor);
	}
	//DONT FORGET TO FREE ag
	desc_token(ag);
	free_strs(ag);
	return (0);
}
