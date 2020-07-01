#include "libft.h"

int		ft_islower(int c)
{
	if (!(c >= 'a' && c <= 'z'))
		return (0);
	return (1);
}
