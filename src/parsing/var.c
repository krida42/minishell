#include "libft.h"
#include "minishell.h"

static int	is_varinit(char *s)
{
	if (*s == '=')
		return (0);
	while (*s)
	{
		if (!(ft_isalnum(*s) || *s == '_'))
			break;
		s++;
	}
	if (*s == '=')
		return (1);
	return (0);
}

void	init_allvar(t_cmd *cmd)
{
	char	**ag;

	ag = cmd->ag;
	while (*ag)
	{

		ag++;
	}
}
