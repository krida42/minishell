#include "minishell.h"


static char	*join_name_nb(char *name, int nb)
{
	char	*nb_s;
	char	*joined;

	nb_s = ft_itoa(nb);
	joined = ft_strjoin(name, nb_s);
	free(nb_s);
	return (joined);
}

static char	*get_available_pathname(void)
{
	char	*pathname;
	int		i;

	pathname = strdup("/tmp/heredocm");
	i = 0;
	while (access(pathname, F_OK) == 0)
	{
		free(pathname);
		pathname = join_name_nb("/tmp/heredocm_", i);
		i++;
	}
	return (pathname);
}

static char	*write_intmp(char *content)
{
	char	*file;
	int		fd;

	file = get_available_pathname();
	fd = open(file, O_WRONLY | O_CREAT,  0644);
	write(fd, content, strlen(content));
	close(fd);
	return (file);
}

static char	*heredoc_child(char *eof)
{
	char	*input;
	char	*content;
	char	*tmp;
	char	*file;

	content = strdup("");
	while (1)
	{
		input = readline("heredoc > ");
		if (!input || strcmp(input, eof) == 0)
		{
			file = write_intmp(content);
			free(input);
			free(content);
			return (file);
		}
		input = ft_strpush(&input, '\n');
		tmp = content;
		content = ft_strjoin(content, input);
		free(tmp);
		free(input);
	}

}

char	*heredoc_start(char *eof)
{
	return(heredoc_child(eof));
}
