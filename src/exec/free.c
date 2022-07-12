/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esmirnov <esmirnov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 19:12:11 by esmirnov          #+#    #+#             */
/*   Updated: 2022/07/01 20:09:42 by esmirnov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_free_ag(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd->ag[i] != NULL)
	{
		free (cmd->ag[i]);
		i++;
	}
}

void	ft_free(t_info *info)
{
	t_cmd	*tmp;

	tmp = info->cmd;
	while (tmp)
	{
		ft_free_ag(tmp);
		free (tmp->ag);
		if (tmp->cmd_path != NULL)
			free (tmp->cmd_path);
		info->cmd = tmp->next;
		free (tmp);
		tmp = info->cmd;
	}
	free (info);
}

void	ft_free_tab(char **tab)
{
	int	i;

	i = 0;
	if (tab != NULL)
	{
		while (tab[i] != NULL)
		{
			free (tab[i]);
			i++;
		}
		free (tab);
	}
}