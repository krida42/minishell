#include "minishell.h"
#include <stdio.h>
void	desc_token(char **strs)
{
	//printf("yo : %s\n", strs[0]);
	
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
		//printf("- - - -\n");
		printf("\n");
	}
	printf("- - - - - - - - -\n");
}

void	desc_info(t_info *info)
{
	int	i;

	i = -1;
	if (!info)
		exit(printf(RED"info is NULL"WHITE));
	printf(CYAN"INFO DESCRIBING\n***********************************\n\n"WHITE);
	desc_allcmd(info->cmd);
	printf("\ninfo->env : \n");
	while (info->env[++i])
		printf("%s\n", info->env[i]);
	printf("\n\ninfo->size : %d\n", info->size);
	printf("info->path : %s\n", info->path);
	printf(CYAN"\n*********************************************\n"WHITE);

}
