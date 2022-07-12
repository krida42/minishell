/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_b.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esmirnov <esmirnov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 19:25:52 by esmirnov          #+#    #+#             */
/*   Updated: 2022/07/01 19:26:35 by esmirnov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipes.h"

void	open_files(t_cmd *cmd)
{
	if (cmd->in)
	{
		cmd->fdin = open(cmd->in, O_RDONLY);
		if (cmd->fdin == -1)
			perror(cmd->in);
	}
	if (cmd->out)
	{
		if (cmd->out)
		{
			cmd->fdout = open(cmd->out, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (cmd->fdout == -1)
				perror(cmd->out);
		}
		else if(cmd->append)
		{
			cmd->fdout = open(cmd->out, O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (cmd->fdout == -1)
				perror(cmd->out);
		}
	}
}

void	open_pipes(t_cmd *cmd, t_info *info) // voir pour free info
{
	while (cmd->next != NULL)
	{
		if (pipe(cmd->pipefd) == -1)
			msg_close_free_exit("pipe failed", info);
		cmd = cmd->next;
	}
}
