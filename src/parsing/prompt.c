#include "libft.h"
#include "minishell.h"
#include <readline/readline.h>

static void	treat_input(char *input, t_info *info)
{
	int	err;

	err = 0;
	if (check_unclosed(input) && ++err)
		ft_putstr_fd(RED"minishell: syntax error: unclosed quotes"
				" forbidden !\n\n"WHITE, 2);
	else if (check_special(input) && ++err)
		ft_putstr_fd(RED"minishell: syntax error: special character"
				" forbidden !\n\n"WHITE, 2);
	else
	{
		if (parse(input, info) == -1 && ++err)
			reset_info(info);
	}
	if (err)
		g_err = 2;
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
			input = ft_strdup("exit");
			//rl_clear_history();
			//close_std();
			//printf("exit\n");
			//free_info(info);
			//return (free(input), 0);
		}
		treat_input(input, info);
		add_history(input);
		free(input);
	}
	return (0);
}
