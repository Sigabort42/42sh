#include "libft.h"

int		ft_index(char *str, char c)
{
	int		i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	if (!str[i])
		return (-1);
	return (i);
}
