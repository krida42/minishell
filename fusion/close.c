/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esmirnov <esmirnov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 19:10:26 by esmirnov          #+#    #+#             */
/*   Updated: 2022/07/06 14:29:59 by esmirnov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipes.h"

void	close_pipes(t_cmd *cmd)
{
	while(cmd->next != NULL)
	{
		close(cmd->pipefd[0]);
		close(cmd->pipefd[1]);
		cmd = cmd->next;
	}
}

void	close_files(t_cmd *cmd)
{
	while(cmd->next)
	{
		close(cmd->fdin);
		close(cmd->fdout);
		cmd = cmd->next;
	}
}

void	close_std(void)
{
	close (STDIN_FILENO); // a voir avec input etc
	close (STDOUT_FILENO); // a voir avec input etc
	close (STDERR_FILENO); // a voir avec input etc
}
