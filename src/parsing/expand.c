/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kisikaya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 19:14:50 by kisikaya          #+#    #+#             */
/*   Updated: 2022/08/01 19:23:24 by kisikaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*next_part(char *s)
{
	char	delimiter;
	int		i;

	i = 0;
	delimiter = *s;
	if (isinset(s[i], "\"'"))
		s++;
	while (s[i])
	{
		if (delimiter == '\'' && s[i] == '\'')
			break ;
		else if (delimiter == '"' && s[i] == '"')
			break ;
		else if (!isinset(delimiter, "\"'") && isinset(s[i], "\"'"))
			break ;
		i++;
	}
	if (isinset(delimiter, "\"'"))
		i++;
	return (s + i);
}

char	*dup_part(char *s)
{
	char	delimiter;
	int		i;

	if (!*s)
		return (ft_strdup(""));
	i = 0;
	delimiter = *s;
	if (isinset(s[i], "\"'"))
		s++;
	while (s[i])
	{
		if (delimiter == '\'' && s[i] == '\'')
			break ;
		else if (delimiter == '"' && s[i] == '"')
			break ;
		else if (!isinset(delimiter, "\"'") && isinset(s[i], "\"'"))
			break ;
		i++;
	}
	return (ft_strndup(s, i));
}

static char	*concatenate(t_env *env, char *s)
{
	char	*joined;
	char	*part;
	char	*tmp;

	joined = ft_strdup("");
	while (*s)
	{
		tmp = joined;
		part = dup_part(s);
		if (*s != '\'')
			var_expand(env, &part);
		joined = ft_strjoin(joined, part);
		free(tmp);
		free(part);
		s = next_part(s);
	}
	return (joined);
}

static char	*manipulate_param(t_env *env, char *s)
{
	char	*concatened;

	if (!s)
		return (NULL);
	concatened = concatenate(env, s);
	free(s);
	return (concatened);
}

int	treat_allparam(t_env *env, t_cmd *cmd, t_info *info)
{
	char	**ag;
	char	*heredoc_path;

	ag = cmd->ag;
	while (ag && *ag)
	{
		*ag = manipulate_param(env, *ag);
		ag++;
	}
	cmd->in = manipulate_param(env, cmd->in);
	cmd->out = manipulate_param(env, cmd->out);
	cmd->append = manipulate_param(env, cmd->append);
	cmd->heredoc = manipulate_param(env, cmd->heredoc);
	if (cmd->heredoc)
	{
		heredoc_path = heredoc_start(info, cmd->heredoc);
		if (!heredoc_path)
			return (-1);
		free(cmd->heredoc);
		cmd->heredoc = heredoc_path;
	}
	return (0);
}
