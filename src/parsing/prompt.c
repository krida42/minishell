	#include "minishell.h"
#include <readline/readline.h>

static void	treat_input(char *input, t_info *info)
{
	if (check_unclosed(input))
		printf(RED"Unclosed quote\n"WHITE);
	else if (check_special(input))
		printf(RED"Special character not authorized\n"WHITE);
	//else
	//	printf("\nYou havre wrote : %s\n\n", input);
	parse(input, info);
}

int	m_prompt(const char *prompt, char **envp)
{
	char	*input;
	t_info	*info;

	info = init_info(envp);
	while (1)
	{
		reset_info(info);
		input = readline(prompt);
		if (!input)//|| ft_strstr(input, "exit") == input)
		{
			rl_clear_history();
			close_std();
			printf("exit\n");
			free_info(info);
			return (free(input), 0);
		}
		//else if (ft_strstr(input, "clear") == input)
		//	rl_clear_history();
		treat_input(input, info);
		add_history(input);
		free(input);
	}
	return (0);
}
