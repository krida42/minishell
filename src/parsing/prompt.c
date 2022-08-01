/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kisikaya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 20:00:49 by kisikaya          #+#    #+#             */
/*   Updated: 2022/08/01 20:00:50 by kisikaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <readline/readline.h>
#include <stdio.h>

static void	treat_input(char *input, t_info *info)
{
	int	err;

	err = 0;
	if (check_unclosed(input) && ++err)
		ft_putstr_fd(RED"minishell: syntax error: unclosed quotes"
			" forbidden !\n\n"WHITE, 2);
	if (err)
		g_err = 2;
	else if (parse(input, info) < 0)
		reset_info(info);
}

int	m_prompt(const char *prompt, char **envp)
{
	char	*input;
	t_info	*info;

	info = init_info(envp);
	input = NULL;
	while (1)
	{
		reset_info(info);
		input = readline(prompt);
		if (!input)
			input = ft_strdup("exit");
		add_history(input);
		treat_input(input, info);
	}
	return (0);
}
