#include "libft.h"

int		ft_isupper(int c)
{
	if (!(c >= 'A' && c <= 'Z'))
		return (0);
	return (1);
}
