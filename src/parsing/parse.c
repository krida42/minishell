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
		if (isinset(input[i], "<>| \t") && !(dquote || squote))
			break;
	}
	if (input[i] == '|' && i == 0)
		i++;
	if (input[i] == ' ' || input[i] == '\t')
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
		if (isinset(input[i], "<>| \t") && !(dquote || squote))
			return (i - 1);
	}
	return (i - 1);
}

static int	set_ag(t_cmd *cmd, char *cursor)
{
	char	*token;
	char	***ag;

	ag = &cmd->ag;
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
	{
		free(cmd->heredoc);
		cmd->heredoc = token;
	}
	else if (append)
	{
		free(cmd->append);
		cmd->append = token;
	}
	else
	{
		if (inout == 0)
		{
			free(cmd->in);
			cmd->in = token;
		}
		else if (inout == 1)
		{
			free(cmd->out);
			cmd->out = token;
		}
	}
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
	i += set_redirect2(cmd, cursor + i, (int[]) {inout, heredoc, append});

	if (isinset(cursor[i], "\"'"))
		i++;
	return (i);
}

static int	set_token(t_cmd **cmd, char *cursor)
{

	if (!*cmd || *cursor == '|')
		add_back(cmd, NULL);
	if  (!isinset(*cursor, "<>|"))
		set_ag(get_last(*cmd), cursor);
	else if (isinset(*cursor, "<>"))
		return (set_redirect(get_last(*cmd), cursor));
	return (0);
}

int	parse(char *input, char **envp)
{
	char	*cursor;
	char	*tmp;
	t_cmd	*cmd;
	t_info	*info;

	cmd = NULL;
	//cursor = input;
	cursor = ft_strtrim(input, " \t");
	tmp = cursor;
	while (cursor && *cursor)
	{
		cursor = cursor + set_token(&cmd, cursor);
		cursor = next_token(cursor);
	}
	free(tmp);
	info = init_info(cmd, envp);
	if(treat_allcmd(info)){
		//desc_info(info);
		execute(info);
	}
	else
		//desc_info(info);
	free_info(info);
	return (0);
}

