#include "libft.h"
#include "minishell.h"
#include <stdio.h>

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

static int	set_ag(t_cmd *cmd, char *cursor)
{
	char	*token;
	char	***ag;

	ag = &get_last(cmd)->ag;
	token = ft_strndup(cursor, end_token_i(cursor) + 1);
	strs_insert(ag, token);
	free(token);
	return (0);
}

static int	set_token(t_cmd **cmd, char *cursor)
{

	if (!*cmd || *cursor == '|')
		add_back(cmd, NULL);
	if  (!isinset(*cursor, "<>|"))
		set_ag(*cmd, cursor);
	//else if (*cursor, "<>")
		//set_redirect()
	//else if (isinset(*cursor, "<>"))
	//	set_redirect()
	return (0);
}

int	parse(char *input)
{
	char	*cursor;
	t_cmd	*cmd;

	cmd = NULL;
	cursor = input;
	while (cursor && *cursor)
	{
		set_token(&cmd, cursor);
		cursor = next_token(cursor);
	}
	//add_back(&cmd, ag);
	desc_allcmd(cmd);
	free_allcmd(cmd);
	return (0);
}
