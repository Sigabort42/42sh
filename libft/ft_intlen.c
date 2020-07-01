#include "libft.h"

int		ft_intlen(int nb)
{
	int	len;

	len = 0;
	while (nb /= 10)
		len++;
	return (len);
}
