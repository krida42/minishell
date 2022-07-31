/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esmirnov <esmirnov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 19:10:26 by esmirnov          #+#    #+#             */
/*   Updated: 2022/07/31 19:40:19 by esmirnov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_pipes(t_cmd *cmd)
{
	while (cmd->next != NULL)
	{
		if (close (cmd->pipefd[0]) == -1)
			g_err = errno;
		if (close (cmd->pipefd[1]) == -1)
			g_err = errno;
		cmd = cmd->next;
	}
}

void	close_files(t_cmd *cmd)
{
	while (cmd)
	{
		if (cmd->fdin >= 0)
		{
			if (cmd->heredoc)
				unlink(cmd->heredoc);
			if (cmd->in || cmd->heredoc)
				close(cmd->fdin);
		}
		if (cmd->fdout >= 0)
		{
			if (cmd->out || cmd->append)
				close (cmd->fdout);
		}
		cmd = cmd->next;
	}
}

void	close_pipes_files(t_cmd *cmd)
{
	close_pipes(cmd);
	close_files(cmd);
}

void	close_std(void)
{
	close (STDIN_FILENO);
	close (STDOUT_FILENO);
	close (STDERR_FILENO);
}
