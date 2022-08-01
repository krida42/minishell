/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kisikaya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 19:34:43 by kisikaya          #+#    #+#             */
/*   Updated: 2022/08/02 01:28:34 by kisikaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

int	err_msg(char *s)
{
	ft_putstr_fd(s, 2);
	return (-1);
}

static void	set_redir_final_inout(t_cmd *cmd, char *token, int inout)
{
	if (inout == 0)
	{
		free(cmd->in);
		cmd->in = token;
	}
	else if (inout == 1)
	{
		free(cmd->out);
		cmd->out = token;
	}
}

static int	set_redir_final(t_cmd *cmd, char *cursor, int *dir)
{
	char		*token;
	const int	inout = dir[0];
	const int	heredoc = dir[1];
	const int	append = dir[2];
	const int	end = end_token_i(cursor);

	token = ft_strndup(cursor, end + 1);
	if (heredoc)
	{
		free(cmd->heredoc);
		cmd->heredoc = token;
	}
	else if (append)
	{
		free(cmd->append);
		cmd->append = token;
	}
	else
		set_redir_final_inout(cmd, token, inout);
	return (end);
}

int	set_redir_iter(char *cursor, int *append, int *heredoc)
{
	int	i;

	*append = 0;
	*heredoc = 0;
	i = 0;
	while (cursor[++i])
	{
		if (isinset(cursor[i], "<>") && (*append || *heredoc))
			return (err_msg(RED"minishell: syntax error near unexpected "
					"token `<' or `>'\n\n" WHITE));
		if (isinset(cursor[i], "<>"))
		{
			if ((cursor[i] == '<' && cursor[i - 1] != '<')
				|| (cursor[i] == '>' && cursor[i - 1] != '>'))
				return (err_msg(RED"minishell: syntax error near unexpected "
						"token `<' or `>'\n\n" WHITE));
			else if (cursor[i] == '<')
				*heredoc = 1;
			else if (cursor[i] == '>')
				*append = 1;
		}
		else
			break ;
	}
	return (i);
}

int	set_redirect(t_cmd *cmd, char *cursor)
{
	int	i;
	int	append;
	int	heredoc;
	int	inout;

	if (!isinset(cursor[0], "<>"))
		exit(printf(RED"DANGER - - set_redirect - - cursor "
				"is not on <> character\n"WHITE));
	inout = cursor[0] == '>';
	i = set_redir_iter(cursor, &append, &heredoc);
	if (i == -1)
		return (-1);
	if (!cursor[i])
		return (err_msg(RED"minishell: syntax error near unexpected "
				"token `<' or `>'\n\n" WHITE));
	if (cursor[i] == ' ')
		i += skip_spaces_i(cursor + i);
	if (cursor[i] == '|')
		return (err_msg(RED"minishell: syntax error near unexpected "
				"token `|'\n\n"WHITE));
	i += set_redir_final(cmd, cursor + i, (int []){inout, heredoc, append});
	if (isinset(cursor[i], "\"'"))
		i++;
	return (i);
}
