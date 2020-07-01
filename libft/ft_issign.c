#include "libft.h"

int		ft_issign(char c)
{
	if (c == '+' || c == '-')
		return (1);
	return (0);
}
