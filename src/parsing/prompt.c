#include "minishell.h"
#include <readline/readline.h>

static void	treat_input(char *input)
{
	if (check_unclosed(input))
		printf(RED"Unclosed quote\n"WHITE);
	else if (check_special(input))
		printf(RED"Special character not authorized\n"WHITE);
	else
		printf("You havre wrote : %s\n", input);
	parse(input);
}

int	m_prompt(const char *prompt)
{
	char	*input;

	while (1)
	{
		input = readline(prompt);
		if (!input || ft_strstr(input, "exit") == input)
		{
			rl_clear_history();
			printf("exit\n");
			return (free(input), 0);
		}
		//else if (ft_strstr(input, "clear") == input)
		//	rl_clear_history();
		treat_input(input);
		add_history(input);
		free(input);
	}
	return (0);
}
