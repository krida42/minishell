#include "libft.h"
#include"minishell.h"
#include <stdio.h>


static int	are_void_cmd(t_cmd *cmd)
{
	while (cmd)
	{
		if (!(cmd->ag || cmd->in || cmd->out || cmd->append || cmd->heredoc))
			return (1);
		cmd = cmd->next;
	}
	return (0);
}

int	is_cmd_err(t_info *info)
{
	if (are_void_cmd(info->cmd))
	{
		info->error_n = 2;
		ft_putstr_fd(RED"minishell: syntax error near unexpected token `|'\n\n"
				WHITE, 2);
		return (1);
	}
	return (0);
}
