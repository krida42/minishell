/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kisikaya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 19:27:21 by kisikaya          #+#    #+#             */
/*   Updated: 2022/08/02 02:00:32 by kisikaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_err = 0;

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	init_signals();
	if (!isatty(1) || !isatty(0))
	{
		err_msg("Pipe from minishell or towards minishell, not allowed, "
			"because not required by the subject !\n");
		exit(0);
	}
	m_prompt(GREEN"minishell ""$> "WHITE, envp);
	return (0);
}
