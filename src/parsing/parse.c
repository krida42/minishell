/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kisikaya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 20:20:55 by kisikaya          #+#    #+#             */
/*   Updated: 2022/08/01 20:21:11 by kisikaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*next_token(char *input)
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
			break ;
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

int	set_token(t_cmd **cmd, char *cursor)
{
	int	ret;

	if (!*cmd || *cursor == '|')
		add_back(cmd, NULL);
	if (!isinset(*cursor, "<>|"))
		set_ag(get_last(*cmd), cursor);
	else if (isinset(*cursor, "<>"))
	{
		ret = set_redirect(get_last(*cmd), cursor);
		g_err = 2;
		return (ret);
	}
	return (0);
}
