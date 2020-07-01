#include "ft_printf.h"

int		ft_is_number(long long nb)
{
	int		i;

	i = 0;
	if (nb == 0)
		return (1);
	else if (nb < 0)
	{
		i++;
		nb *= -1;
	}
	while (nb > 0)
	{
		nb /= 10;
		i++;
	}
	return (i);
}
