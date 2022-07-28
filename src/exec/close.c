/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esmirnov <esmirnov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 19:10:26 by esmirnov          #+#    #+#             */
/*   Updated: 2022/07/28 08:45:54 by esmirnov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_pipes(t_cmd *cmd) //20220717 ok
{
	while(cmd->next != NULL)
	{
		close(cmd->pipefd[0]);
		close(cmd->pipefd[1]);
		cmd = cmd->next;
	}
}

void	close_files(t_cmd *cmd) //20220717 ok
{
	while(cmd)
	{
		if (cmd->in || cmd->heredoc)
			close(cmd->fdin);
		if (cmd->out || cmd->append)
			close(cmd->fdout);
		cmd = cmd->next;
	}
}

void	close_cmd_files(t_cmd *cmd) //20220717 ok
{
	if (cmd->in || cmd->heredoc)
		close(cmd->fdin);
	if (cmd->out || cmd->append)
		close(cmd->fdout);
}

void	close_pipescmd_files(t_cmd *cmd)
{
	close_pipes(cmd);
	close_cmd_files(cmd);
}

void	close_pipes_files(t_cmd *cmd)
{
	close_pipes(cmd);
	close_files(cmd);
}

void	close_std(void) //20220717 ok
{
	close (STDIN_FILENO); // a voir avec input etc
	close (STDOUT_FILENO); // a voir avec input etc
	close (STDERR_FILENO); // a voir avec input etc
}
