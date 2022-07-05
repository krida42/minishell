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
		printf("- - - -\n");
	}
}
