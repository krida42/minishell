#include "libft.h"
#include "minishell.h"
#include <stdio.h>

/*
static char	*next_token(char *input)
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
	int	dquote;
	int	squote;

	dquote = 0;
	squote = 0;
	i = -1;
	while (input[++i])
	{
		if (input[i] == '\'' && !dquote)
			squote = !squote;
		else if (input[i] == '"' && !squote)
			dquote = !dquote;
		if (isinset(input[i], "<>| ") && !(dquote || squote))
			break;
	}
	if (input[i] == ' ')
		i += skip_spaces_i(input + i);
	
	return (input + i);
}

static int	end_token_i(char *input)
{
	int	i;
	int	dquote;
	int	squote;

	dquote = 0;
	squote = 0;

	i = -1;
	while (input[++i])
	{
		if (input[i] == '\'' && !dquote)
			squote = !squote;
		else if (input[i] == '"' && !squote)
			dquote = !dquote;
		if (isinset(input[i], "<>| ") && !(dquote || squote))
			return (i - 1);
	}
	return (i - 1);
}

static int	set_ag(char ***ag, char *cursor)
{
	char	*token;

	token = ft_strndup(cursor, end_token_i(cursor) + 1);
	strs_insert(ag, token);
	free(token);
	return (0);
}

int	parse(char *input)
{
	char	*cursor;
	char	**ag;
	t_cmd	*cmd;

	cmd = NULL;
	ag = NULL;
	cursor = input;
	while (cursor && *cursor)
	{
		set_ag(&ag, cursor);
		cursor = next_token(cursor);
	}
	add_back(&cmd, ag);
	//DONT FORGET TO FREE ag
	//desc_token(ag);
	desc_allcmd(cmd);
	free_allcmd(cmd);
	//free_strs(ag);
	return (0);
}
