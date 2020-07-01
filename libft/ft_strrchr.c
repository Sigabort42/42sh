#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int				i;

	i = ft_strlen((char*)s);
	if (s[0] == c && !s[0])
		return ((char*)s);
	if (s[0])
	{
		while (i >= 0)
		{
			if (s[i] == c)
				return ((char*)&s[i]);
			i--;
		}
	}
	return (0);
}
