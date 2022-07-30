/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esmirnov <esmirnov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 19:10:26 by esmirnov          #+#    #+#             */
/*   Updated: 2022/07/30 16:58:17 by esmirnov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_pipes(t_cmd *cmd) //20220717 ok
{
	// fprintf(stderr,"close_pipes START\t\t\t\t\t\terrno is\t%d\n", errno);
	while(cmd->next != NULL)
	{
		// fprintf(stderr,"\tclose pipe middle before close\tcmd->pipefd[0] =%d\terrno is\t%d\n", cmd->pipefd[0], errno);
		close(cmd->pipefd[0]);
		// fprintf(stderr,"\tclose pipe middle after close\tcmd->pipefd[0] =%d\terrno is\t%d\n", cmd->pipefd[0], errno);
		// fprintf(stderr,"\tclose pipe middle before close\tcmd->pipefd[1] =%d\terrno is\t%d\n", cmd->pipefd[1], errno);
		close(cmd->pipefd[1]);
		// fprintf(stderr,"\tclose pipe middle after close\tcmd->pipefd[1] =%d\terrno is\t%d\n", cmd->pipefd[1], errno);
		cmd = cmd->next;
	}
	// fprintf(stderr,"close pipe END\t\t\t\t\t\terrno is\t%d\n\n", errno);
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
