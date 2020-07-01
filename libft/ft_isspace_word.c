#include "libft.h"

int	ft_isspace_word(char *s)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] == ' ' || s[i] == '\t')
			j++;
		i++;
	}
	return (j);
}
