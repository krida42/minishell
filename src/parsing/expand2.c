/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kisikaya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 20:02:54 by kisikaya          #+#    #+#             */
/*   Updated: 2022/08/01 20:02:55 by kisikaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>

static int	end_var_i(char *cursor)
{
	int		i;

	if (*cursor != '$')
		exit(printf(RED"DANGER -- dup_var_substi - trying to get val while "
				"expanding but cursor not on $\n"WHITE));
	i = 1;
	if (cursor[i] == '?')
		return (i);
	else if (!(ft_isalnum(cursor[i]) || cursor[i] == '_'))
		return (-1);
	while (cursor[i] && (ft_isalnum(cursor[i]) || cursor[i] == '_'))
		i++;
	return (i - 1);
}

static char	*dup_var_substi(t_env *env, char *cursor, int len)
{
	char	*name;
	char	*val;

	name = ft_strndup(cursor + 1, len - 1);
	if (*name == '?')
		val = ft_itoa(g_err);
	else
		val = env_get_val(env, name);
	if (!val)
		val = ft_strdup("");
	free(name);
	return (val);
}

static char	*next_part(t_env *env, char *str, char **part)
{
	int	end_i;

	if (*str == '$')
	{
		end_i = end_var_i(str);
		if (end_i == -1 && end_i++)
			*part = ft_strdup("$");
		else
			*part = dup_var_substi(env, str, end_i + 1);
		str += end_i;
		if (*str)
			str++;
	}
	else
	{
		end_i = 0;
		while (str[end_i] && str[end_i] != '$')
			end_i++;
		*part = ft_strndup(str, end_i);
		str += end_i;
	}
	return (str);
}

void	var_expand(t_env *env, char **s)
{
	char	*str;
	char	*joined;
	char	*part;
	char	*tmp;

	str = *s;
	if (!ft_strchr(str, '$'))
		return ;
	joined = ft_strdup("");
	while (*str)
	{
		str = next_part(env, str, &part);
		tmp = joined;
		joined = ft_strjoin(joined, part);
		free(part);
		free(tmp);
	}
	free(*s);
	*s = joined;
}
