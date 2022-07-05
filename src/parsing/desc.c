#include "minishell.h"
#include <stdio.h>
void	desc_token(char **strs)
{
	//printf("yo : %s\n", strs[0]);
	
	if (!strs)
		printf("no token strs NULL\n");
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
		cmd = cmd->next;
		printf("- - - -\n");
	}
}
