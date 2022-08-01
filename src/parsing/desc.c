/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   desc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kisikaya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 19:26:27 by kisikaya          #+#    #+#             */
/*   Updated: 2022/08/01 19:26:28 by kisikaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	desc_token(char **strs)
{
	if (!strs)
		printf("no token_ag strs NULL\n");
	while (strs && *strs)
	{
		printf("token : |%s|\n", *strs);
		strs++;
	}
}

void	desc_allcmd(t_cmd *cmd)
{
	while (cmd)
	{
		printf("cmd - - - -\n");
		desc_token(cmd->ag);
		if (cmd->in)
			printf("in : %s\n", cmd->in);
		if (cmd->out)
			printf("out : %s\n", cmd->out);
		if (cmd->heredoc)
			printf("heredoc : %s\n", cmd->heredoc);
		if (cmd->append)
			printf("append : %s\n", cmd->append);
		cmd = cmd->next;
		printf("\n");
	}
	printf("- - - - - - - - -\n");
}

void	desc_info(t_info *info)
{
	if (!info)
		exit(printf(RED"info is NULL"WHITE));
	printf(CYAN"INFO DESCRIBING\n***********************************\n\n"WHITE);
	desc_allcmd(info->cmd);
	printf("\n\ninfo->size : %d\n", info->size);
	printf(CYAN"\n*********************************************"WHITE"\n");
}
