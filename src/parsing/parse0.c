/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse0.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kisikaya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 20:36:35 by kisikaya          #+#    #+#             */
/*   Updated: 2022/08/01 20:37:23 by kisikaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parse_iter(char *cursor, char *tmp, t_cmd **cmd)
{
	int	ret;

	ret = 0;
	while (cursor && *cursor)
	{
		ret = set_token(cmd, cursor);
		if (ret == -1)
		{
			free_allcmd(*cmd);
			free(tmp);
			return (-1);
		}
		cursor = cursor + ret;
		cursor = next_token(cursor);
	}
	return (ret);
}

int	parse(char *input, t_info *info)
{
	char	*cursor;
	char	*tmp;
	t_cmd	*cmd;
	int		ret;

	cmd = NULL;
	cursor = ft_strtrim(input, " \t");
	tmp = cursor;
	free(input);
	if (parse_iter(cursor, tmp, &cmd) == -1)
		return (-1);
	free(tmp);
	set_cmd(info, cmd);
	if (is_cmd_err(info))
		return (-2);
	ret = treat_allcmd(info);
	if (ret == 1)
		g_err = execute(info);
	return (ret);
}
