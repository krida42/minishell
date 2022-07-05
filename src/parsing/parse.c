#include "libft.h"
#include "minishell.h"
#include <stdio.h>
#include <string.h>

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

static int	set_redirect2(t_cmd *cmd, char *cursor, int *dir)
{
	char	*token;
	const int	inout = dir[0];
	const int	heredoc = dir[1];
	const int	append = dir[2];
	const int	end = end_token_i(cursor);

	token = ft_strndup(cursor, end + 1);

	if (heredoc)
		cmd->heredoc = token;
	else if (append)
		cmd->append = token;
	else 
		if (inout == 0)
			cmd->in = token;
		else if (inout == 1)
			cmd->out = token;
	return (end);

}

static int	set_redirect(t_cmd *cmd, char *cursor)
{
	int	i;
	int	append;
	int	heredoc;
	int	inout;

	append = 0;
	heredoc = 0;
	i = 0;
	if (!isinset(cursor[i], "<>"))
		exit(printf(RED"DANGER - - set_redirect - - cursor is not on <> character"WHITE));
	inout = cursor[i] == '>';
	while (cursor[++i])
	{
		if (isinset(cursor[i], "<>") && (append || heredoc))
			exit(printf(RED"Later in return: forbidden input too much >>> <<<"WHITE));
		if (isinset(cursor[i], "<>"))
		{
			if ((cursor[i] == '<' && cursor[i - 1] != '<') || (cursor[i] == '>' && cursor[i - 1] != '>'))
				exit(printf(RED"Later in return: forbidden input <>" WHITE));
			else if (cursor[i] == '<')
				heredoc = 1;
			else if (cursor[i] == '>')
				append = 1;
		}
		else
			break ;

	}
	if (!cursor[i])
		exit(printf(RED"Later in return: forbidden input  > or < in last character" WHITE));
	i += skip_spaces_i(cursor + i);
	i = set_redirect2(cmd, cursor + i, (int[]) {inout, heredoc, append});
	return (i);
}

static int	set_token(t_cmd **cmd, char *cursor)
{

	if (!*cmd || *cursor == '|')
		add_back(cmd, NULL);
	if  (!isinset(*cursor, "<>|"))
		set_ag(*cmd, cursor);
	else if (isinset(*cursor, "<>"))
	{
		printf("salut ! \n");
		return (set_redirect(*cmd, cursor));
	}
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
		cursor = cursor + set_token(&cmd, cursor);
		cursor = next_token(cursor);
	}
	//add_back(&cmd, ag);
	desc_allcmd(cmd);
	free_allcmd(cmd);
	return (0);
}
