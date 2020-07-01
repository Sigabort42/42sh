#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	int		i;

	if (ft_strcmp(haystack, needle) == 0)
		return ((char*)haystack);
	if (haystack[0])
	{
		i = 0;
		while (needle[i])
		{
			if (needle[i] != haystack[i])
				return (ft_strstr((char*)haystack + 1, needle));
			i = i + 1;
		}
		return ((char*)haystack);
	}
	else
		return (0);
}
