#include "libft.h"

int		ft_strchri(const char *s, char c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	if (s[i] == c)
		return (i);
	return (-1);
}

char	*ft_strstr(const char *big, const char *little)
{
	return (ft_strnstr(big, little, ft_strlen(big)));
}
