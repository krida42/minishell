/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esmirnov <esmirnov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 19:10:26 by esmirnov          #+#    #+#             */
/*   Updated: 2022/07/30 19:53:22 by esmirnov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_pipes(t_cmd *cmd) //20220717 ok
{
	// fprintf(stderr,"g_err = %d\terrno = %d\tclose_pipes START\t\t\t\t\t\t\n", g_err, errno);
	while(cmd->next != NULL)
	{
		// fprintf(stderr,"g_err = %d\terrno = %d\tcmd->pipefd[0] =%d\ti = %d close pipe middle before close\n", g_err, errno, cmd->pipefd[0], i);
		if (close(cmd->pipefd[0]) == -1)
			g_err = errno;
		// fprintf(stderr,"g_err = %d\terrno = %d\tcmd->pipefd[0] =%d\ti = %d close pipe middle after close\t\n", g_err, errno, cmd->pipefd[0], i);
		// fprintf(stderr,"g_err = %d\terrno = %d\tcmd->pipefd[1] =%d\ti = %d close pipe middle before close\t\n", g_err, errno, cmd->pipefd[1], i);
		if (close(cmd->pipefd[1]) == -1)
			g_err = errno;
		// fprintf(stderr,"g_err = %d\terrno = %d\tcmd->pipefd[1] =%d\t\ti = %d close pipe middle after close\t\n", g_err, errno, cmd->pipefd[1], i);
		cmd = cmd->next;
	}
	// fprintf(stderr,"g_err = %d\terrno = %d\tclose pipe END\t\t\t\t\t\t\n\n", g_err, errno);
}

void	close_files(t_cmd *cmd) //20220717 ok
{
	while(cmd)
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
				close(cmd->fdout);
		}
		cmd = cmd->next;
	}
}

// void	close_cmd_files(t_cmd *cmd) //20220717 ok
// {
// 	if (cmd->in || cmd->heredoc)
// 		close(cmd->fdin);
// 	if (cmd->out || cmd->append)
// 		close(cmd->fdout);
// }

// void	close_pipescmd_files(t_cmd *cmd)
// {
// 	close_pipes(cmd);
// 	close_cmd_files(cmd);
// }

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
