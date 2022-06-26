#include "libft.h"
#include "minishell.h"

int	strs_len(char **strs)
{
	int	i;

	i = 0;
	while (strs && strs[i])
		i++;
	return (i);
}

char	**strs_insert(char ***strs, const char *s)
{
	int		new_len;
	char	**new_strs;
	int		i;

	new_len = strs_len(*strs) + 1;
	new_strs = malloc(sizeof(char *) * (new_len + 1));
	if (!*strs)
	{
		new_strs[0] = strdup(s);
		new_strs[1] = NULL;
		*strs = new_strs;
		return (new_strs);
	}
	i = -1;
	while ((*strs)[++i])
		new_strs[i] = (*strs)[i];
	new_strs[i++] = strdup(s);
	new_strs[i] = NULL;
	free(*strs);
	*strs = new_strs;
	return (new_strs);
}

int	isinset(char c, const char *set)
{
	while (*set)
		if (*set++ == c)
			return (1);
	return (0);
}
