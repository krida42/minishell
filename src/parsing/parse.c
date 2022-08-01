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

int	end_token_i(char *input)
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



static int	set_token(t_cmd **cmd, char *cursor)
{
	int	ret;

	if (!*cmd || *cursor == '|')
		add_back(cmd, NULL);
	if  (!isinset(*cursor, "<>|"))
		set_ag(get_last(*cmd), cursor);
	else if (isinset(*cursor, "<>"))
	{
		ret = set_redirect(get_last(*cmd), cursor);
		g_err = 2;
		return (ret);
	}
	return (0);
}

int	parse(char *input, t_info *info)
{
	char	*cursor;
	char	*tmp;
	t_cmd	*cmd;
	int		ret;

	cmd = NULL;
	//cursor = input;
	cursor = ft_strtrim(input, " \t");
	tmp = cursor;
	free(input);
	while (cursor && *cursor)
	{
		ret = set_token(&cmd, cursor);
		if (ret == -1)
		{
			free_allcmd(cmd);
			free(tmp);
			return (-1);
		}
		cursor = cursor + ret;
		cursor = next_token(cursor);
	}
	free(tmp);
	set_cmd(info, cmd);
	if (is_cmd_err(info))
		return (-2);
	ret = treat_allcmd(info);
	//if (ret == -1)
	//	return -1;
	printf("ret : %d\n", ret);
	if (ret == 1){
		desc_info(info);
		g_err = execute(info);
	}
	else if (ret == 0)
		desc_info(info);
	return (ret);
}

