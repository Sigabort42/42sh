#include "libft.h"

char	*ft_strndup(const char *s, int n, int for_free)
{
	char	*str;

	if (n == 0)
		return ((char*)s);
	str = (char *)malloc(sizeof(*str) * (n + 1));
	ft_strncpy(str, s, n);
	str[n] = '\0';
	if (for_free)
		free((char*)s);
	return (str);
}
