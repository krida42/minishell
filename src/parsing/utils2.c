#include <minishell.h>

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

int	skip_spaces_i(char *s)
{
	char	*ns;

	ns = skip_spaces(s);
	return (ns - s);
}
