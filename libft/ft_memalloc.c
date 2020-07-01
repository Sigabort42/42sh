#include "libft.h"

void	*ft_memalloc(size_t size)
{
	char			*str;
	size_t			i;

	i = 0;
	if (size > 4294967295)
		return (0);
	if ((str = (char*)malloc(sizeof(*str) * size + 1)) == 0)
		return (0);
	while (i < size)
		str[i++] = 0;
	return ((void *)str);
}
