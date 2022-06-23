#include <stdio.h>
void	desc_token(char **strs)
{
	printf("yo : %s\n", strs[0]);
	
	while (strs && *strs)
	{
		printf("token : %s\n", *strs);
		strs++;
	}
}
