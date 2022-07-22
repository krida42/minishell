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

void	init_allvar(t_cmd *cmd)
{
	char	**ag;
	int		i;

	ag = cmd->ag;
	i = 0;
	//Les cas ou l'initialiasaiotn ' de variable est annule
	if (!are_allvarinit(ag) || cmd->next || cmd->prev)
	{
		printf("ag[0]: %s\n", ag[0]);
		while (ag && ag[i])
		{
			printf("i: %d\n", i);
			if (is_varinit(ag[i]))
			{
				printf("INIT\n");
				strs_remove(&ag, i);
				i = 0;
				continue;
			}
			i++;
		}
	}
	if (!ag[0])
	{
		free_strs(ag);
		ag = NULL;
	}
	cmd->ag = ag;
}
