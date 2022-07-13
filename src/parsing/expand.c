#include "libft.h"
#include "minishell.h"

static char	*next_part(char *s)
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
	if (s[i])
		i++;
	return (s + i);

}

static char	*dup_part(char *s)
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

	//var_expanded = var_expand(*s);
	concatened = concatenate(s);
	return (concatened);
}

static void	treat_allparam(char **ag)
{
	char	*tmp;

	while (*ag)
	{
		tmp = *ag;
		*ag = manipulate_param(*ag);
		free(tmp);
		ag++;
	}
}

void	treat_allcmd(t_cmd *cmd)
{
	while (cmd)
	{
		treat_allparam(cmd->ag);
		cmd = cmd->next;
	}
}

