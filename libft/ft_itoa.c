#include "libft.h"

char		*ft_itoa(int n)
{
	int		i;
	char	*new;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	i = 0;
	new = ft_strnew(12);
	if (n < 0 && (n *= -1))
		new[i++] = '-';
	while (n)
	{
		new[i++] = (n % 10) + '0';
		n /= 10;
	}
	return (ft_strndup(new, i, 1));
}
