/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand0.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kisikaya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 19:22:44 by kisikaya          #+#    #+#             */
/*   Updated: 2022/08/01 19:22:45 by kisikaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	treat_allcmd(t_info *info)
{
	t_cmd	*cmd;
	int		ret;

	ret = 0;
	cmd = info->cmd;
	while (cmd)
	{
		ret = clearify_allvar(cmd);
		if (treat_allparam(info->env, cmd, info) == -1)
			return (-1);
		if (!ret)
			init_allvar(&info->env, cmd);
		cmd = cmd->next;
	}
	return (ret);
}
