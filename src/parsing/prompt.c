#include "minishell.h"
#include <readline/readline.h>

static void	treat_input(char *input, char **envp)
{
	if (check_unclosed(input))
		printf(RED"Unclosed quote\n"WHITE);
	else if (check_special(input))
		printf(RED"Special character not authorized\n"WHITE);
	//else
	//	printf("\nYou havre wrote : %s\n\n", input);
	parse(input, envp);
}

int	m_prompt(const char *prompt, char **envp)
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
		treat_input(input, envp);
		add_history(input);
		free(input);
	}
	return (0);
}
