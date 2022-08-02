/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kisikaya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 19:12:36 by kisikaya          #+#    #+#             */
/*   Updated: 2022/08/02 02:09:03 by kisikaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

static int	are_void_cmd(t_cmd *cmd)
{
	while (cmd)
	{
		if (!(cmd->ag || cmd->in || cmd->out || cmd->append || cmd->heredoc))
			return (1);
		cmd = cmd->next;
	}
	return (0);
}

int	is_cmd_err(t_info *info)
{
	if (are_void_cmd(info->cmd))
	{
		ft_putstr_fd(RED"minishell: syntax error near unexpected token `|'\n\n"
			WHITE, 2);
		g_err = 2;
		return (1);
	}
	return (0);
}
