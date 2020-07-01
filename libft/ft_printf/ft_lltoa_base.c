#include "ft_printf.h"

static int		ft_count(unsigned long long value, int base)
{
	int		i;

	i = 0;
	if (value == 0)
		return (1);
	while (value > 0)
	{
		i++;
		value /= base;
	}
	return (i);
}

char			*ft_lltoa_base(unsigned long long value, int base)
{
	char		*res;
	int			i;

	res = NULL;
	if (base == 10)
		return (res = ft_lltoa(value));
	i = ft_count(value, base);
	res = (char*)malloc(sizeof(char) * i);
	res[i] = 0;
	while (i-- > 0)
	{
		res[i] = value % base + ((value % base > 9) ? 'a' - 10 : '0');
		value /= base;
	}
	return (res);
}
