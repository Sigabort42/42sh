#include "libft.h"

int	ft_putstr(char const *s)
{
	int	size;

	size = 0;
	if (s)
	{
		write(1, s, ft_strlen(s));
		size = ft_strlen(s);
	}
	return (size);
}
