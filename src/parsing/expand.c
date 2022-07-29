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

static char	*concatenate(t_env *env, char *s, int err)
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
			var_expand(env, &part, err);
		joined = ft_strjoin(joined, part);
		free(tmp);
		free(part);
		s = next_part(s);
	}
	return (joined);
}

static char	*manipulate_param(t_env *env, char *s, int err)
{
	char	*concatened;

	if (!s)
		return (NULL);
	concatened = concatenate(env, s, err);
	free(s);
	return (concatened);
}

static void	treat_allparam(t_env *env, t_cmd *cmd, t_info *info)
{
	char	**ag;
	char	*heredoc_path;

	ag = cmd->ag;
	while (ag && *ag)
	{
		*ag = manipulate_param(env, *ag, info->error_n);
		ag++;
	}
	cmd->in = manipulate_param(env, cmd->in, info->error_n);
	cmd->out = manipulate_param(env, cmd->out, info->error_n);
	cmd->append = manipulate_param(env, cmd->append, info->error_n);
	cmd->heredoc = manipulate_param(env, cmd->heredoc, info->error_n);
	if (cmd->heredoc)
	{
		heredoc_path = heredoc_start(info, cmd->heredoc);
		if (heredoc_path)
		{
			free(cmd->heredoc);
			cmd->heredoc = heredoc_path;
		}
	}
}

int		treat_allcmd(t_info *info)
{
	t_cmd	*cmd;
	int		ret;

	cmd = info->cmd;
	while (cmd)
	{
		ret = clearify_allvar(cmd);
		treat_allparam(info->env, cmd, info);
		if (!ret)
			init_allvar(&info->env, cmd);
		cmd = cmd->next;
	}
	return (ret);
}

