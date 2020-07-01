#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((unsigned char *)dst)[i] = ((unsigned char *)src)[i];
		i++;
		if (((unsigned char *)src)[i - 1] == (unsigned char)c)
			return (dst + i);
	}
	return (0);
}
