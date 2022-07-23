#include "libft.h"
#include "minishell.h"
#include <stdio.h>

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

static	int	are_allvarinit(char **ag)
{
	while (*ag)
	{
		if (!is_varinit(*ag))
			return (0);
		ag++;
	}
	return (1);
}

int	init_allvar(t_cmd *cmd)
{
	char	**ag;
	int		i;

	ag = cmd->ag;
	i = -1;
	//Les cas ou l'initialiasaiotn ' de variable est annule
	if (!are_allvarinit(ag) || cmd->next || cmd->prev)
	{
		while (ag && ag[++i])
		{
			printf("i: %d\n", i);
			if (is_varinit(ag[i]))
			{
				strs_remove(&ag, i);
				i = -1;
			}
			else
				break;
		}
	}
	else
		return (0);
	if (!ag[0])
	{
		free_strs(ag);
		ag = NULL;
	}
	cmd->ag = ag;
	return (1);
}
