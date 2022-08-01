/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kisikaya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 20:01:10 by kisikaya          #+#    #+#             */
/*   Updated: 2022/08/01 20:01:11 by kisikaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_cmd(t_cmd *cmd)
{
	free_strs(cmd->ag);
	free(cmd->in);
	free(cmd->out);
	free(cmd->append);
	free(cmd->heredoc);
	free(cmd->cmd_path);
	free(cmd);
}

void	free_allcmd(t_cmd *cmd)
{
	if (!cmd)
		return ;
	while (cmd->next)
	{
		cmd = cmd->next;
		free_cmd(cmd->prev);
	}
	free_cmd(cmd);
}
