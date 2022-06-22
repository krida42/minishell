#include "color.h"
#include "minishell.h"

int	main(void)
{	
	init_signals();
	m_prompt(GREEN"minishell ""$> "WHITE);
	return (0);
}
