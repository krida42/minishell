/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kisikaya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 19:31:35 by kisikaya          #+#    #+#             */
/*   Updated: 2022/08/01 19:31:36 by kisikaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
/*
char	*skip_spaces(char *s)
{
	if (!*s)
		exit(printf(RED"DANGER - - skip_spaces - - Already at end of *s"WHITE));
	if (s[0] != ' ' && s[1] != ' ')
		return (s);
	while (*++s && *s == ' ')
		;
	return (s);

}
*/

char	*skip_spaces(char *s)
{
	if (!*s)
		exit(printf(RED"DANGER - - skip_spaces - - Already at end of *s"WHITE));
	if (!ft_isblank(s[0]) && !ft_isblank(s[1]))
		return (s);
	while (*++s && ft_isblank(*s))
		;
	return (s);
}

int	skip_spaces_i(char *s)
{
	char	*ns;

	ns = skip_spaces(s);
	return (ns - s);
}

void	ft_puterr(char *s, char *s1, char *s2)
{
	if (s)
		ft_putstr_fd(s, 2);
	if (s1)
		ft_putstr_fd(s1, 2);
	if (s2)
		ft_putstr_fd(s2, 2);
}

char	*ft_strpush(char **s, char c)
{
	int		i;
	int		len;
	char	*joined;

	if (*s)
		len = ft_strlen(*s);
	else
		len = 0;
	joined = ft_calloc(len + 2, sizeof(char));
	i = 0;
	while (*s && (*s)[i])
	{
		joined[i] = (*s)[i];
		i++;
	}
	joined[i] = c;
	free(*s);
	*s = joined;
	return (joined);
}
