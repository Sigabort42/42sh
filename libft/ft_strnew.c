#include "libft.h"

char	*ft_strnew(size_t size)
{
	unsigned char	*str;
	size_t			i;

	i = 0;
	if ((str = (unsigned char *)malloc(sizeof(*str) * size + 1)) == 0)
		return (0);
	while (i <= size)
		str[i++] = 0;
	return ((char*)str);
}
