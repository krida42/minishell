#include "color.h"
#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	init_signals();
	m_prompt(GREEN"minishell ""$> "WHITE, envp);
	return (0);
}
