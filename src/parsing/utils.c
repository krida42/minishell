#include "libft.h"
#include "minishell.h"

int	strs_len(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
		i++;
	return (i);
}

char	**strs_insert(const char *s, char **strs)
{
	int		new_len;
	char	**new_strs;
	int		i;

	if (!strs)
	{
		new_strs = malloc(sizeof(char *) * 2);
		new_strs[0] = ft_strdup(s);
		new_strs[1] = NULL;
		return (new_strs);
	}
	new_len = strs_len(strs) + 1;
	new_strs = malloc(sizeof(char *) * (new_len + 1));
	i = 0;
	while (strs[++i])
		new_strs[i] = strs[i];
	new_strs[i++] = ft_strdup(s);
	new_strs[i] = NULL;
	return (new_strs);
}
