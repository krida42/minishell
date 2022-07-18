#include "libft.h"
#include "minishell.h"
#include <stdio.h>

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
			break;
		else if (delimiter == '"' && s[i] == '"')
			break;
		else if (!isinset(delimiter, "\"'") && isinset(s[i], "\"'"))
			break;
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
			break;
		else if (delimiter == '"' && s[i] == '"')
			break;
		else if (!isinset(delimiter, "\"'") && isinset(s[i], "\"'"))
			break;
		i++;
	}

	return (ft_strndup(s, i));
}

static char	*concatenate(char *s)
{
	char	*joined;
	char	*part;
	char	*tmp;

	joined = ft_strdup("");
	while (*s)
	{
		tmp = joined;
		part = dup_part(s);
		joined = ft_strjoin(joined, part);
		free(tmp);
		free(part);
		s = next_part(s);
	}
	return (joined);
}

static char	*manipulate_param(char *s)
{
	//char	*var_expanded;
	char	*concatened;

	if (!s)
		return (NULL);
	//var_expanded = var_expand(*s);
	concatened = concatenate(s);
	free(s);
	return (concatened);
}

static void	treat_allparam(t_cmd *cmd)
{
	char	**ag;

	ag = cmd->ag;
	while (*ag)
	{
		*ag = manipulate_param(*ag);
		ag++;
	}
	cmd->in = manipulate_param(cmd->in);
	cmd->out = manipulate_param(cmd->out);
	cmd->append = manipulate_param(cmd->append);
	cmd->heredoc = manipulate_param(cmd->heredoc);
}

void	treat_allcmd(t_info *info)
{
	t_cmd	*cmd;

	cmd = info->cmd;
	while (cmd)
	{
		treat_allparam(cmd);
		cmd = cmd->next;
	}
}

