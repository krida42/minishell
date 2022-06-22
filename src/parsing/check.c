#include "minishell.h"

int	check_special(char *input)
{
	while (*input)
	{
		if (*input == '\\' || *input == ';')
			return (1);
		input++;
	}
	return (0);
}

int	check_unclosed(char *input)
{
	int	squotes_times;
	int	dquotes_times;

	squotes_times = 0;
	dquotes_times = 0;
	while (*input)
	{
		if (*input == '\'')
			squotes_times++;
		else if (*input == '"')
			dquotes_times++;
		input++;
	}
	return (squotes_times % 2 || dquotes_times % 2);
}
