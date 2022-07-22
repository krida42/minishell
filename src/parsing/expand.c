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

static void	treat_allparam(t_env *env, t_cmd *cmd)
{
	char	**ag;

	ag = cmd->ag;
	while (*ag)
	{
		*ag = manipulate_param(env, *ag);
		ag++;
	}
	cmd->in = manipulate_param(env, cmd->in);
	cmd->out = manipulate_param(env, cmd->out);
	cmd->append = manipulate_param(env, cmd->append);
	cmd->heredoc = manipulate_param(env, cmd->heredoc);
}

void	treat_allcmd(t_info *info)
{
	t_cmd	*cmd;

	cmd = info->cmd;
	while (cmd)
	{
		//init_allvar(cmd);
		treat_allparam(info->env ,cmd);
		cmd = cmd->next;
	}
}

