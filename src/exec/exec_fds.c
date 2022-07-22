/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_fds.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esmirnov <esmirnov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 14:27:07 by esmirnov          #+#    #+#             */
/*   Updated: 2022/07/22 14:58:24 by esmirnov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	save_stdinout(int n) //20220717 ok
{
	static int	tmpin;
	static int	tmpout;

	if (n == 1)
	{
		tmpin = dup(STDIN_FILENO);
		tmpout = dup(STDOUT_FILENO);
	}
	if (n == 2)
	{
		if (dup2(tmpin, STDIN_FILENO) == -1)
		{
			perror("dup2 failed save_stdinout 2 temp in");
			return (1);
		}
		close(tmpin);
		if (dup2(tmpout, STDOUT_FILENO) == -1)
		{
			perror("dup2 failed save_stdinout  2 temp in");
			return (1);
		}
		close(tmpout);
	}
	return (0);
}

int	dup_filefds(t_cmd *cmd, t_info *info) //20220717 ok
{
	if (cmd->in != NULL || cmd->heredoc != NULL)
	{
		if (dup2(cmd->fdin, STDIN_FILENO) == -1)
		{
			perror("dup2 failed dup_filefds in ");
			close_files(info->cmd);
			exit (EXIT_FAILURE);
		}
	}
	if (cmd->out != NULL || cmd->append != NULL)
	{
		if (dup2(cmd->fdout, STDOUT_FILENO) == -1)
		{
			perror("dup2 failed dup_filefds out ");
			close_files(info->cmd);
			exit (EXIT_FAILURE);
		}
	}
	return (0);
}

int	dup_pipefds(t_cmd *cmd, t_info *info)
{
	if (cmd->prev != NULL && cmd->in == NULL && cmd->heredoc == NULL) // && cmd->prev->out == NULL && cmd->prev->append == NULL
	{
		if (dup2(cmd->prev->pipefd[0], STDIN_FILENO) == -1)
		{
			perror("dup2 failed dup_pipefds in ");
			close_pipes(info->cmd);
			exit (EXIT_FAILURE);
		}
	}
	if (cmd->next != NULL && cmd->out == NULL && cmd->append == NULL) //&& cmd->next->in == NULL && cmd->next->heredoc == NULL
	{
		if (dup2(cmd->pipefd[1], STDOUT_FILENO) == -1)
		{
			perror("dup2 failed dup_pipefds in ");
			close_pipes(info->cmd);
			exit (EXIT_FAILURE);
		}
	}
	return (0);
}