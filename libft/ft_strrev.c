#include "libft.h"

char		*ft_strrev(char *str)
{
	int		i;
	int		len;
	char	swap;

	i = 0;
	len = ft_strlen(str) - 1;
	while (i < len - i)
	{
		swap = str[i];
		str[i] = str[len - i];
		str[i - len] = swap;
		i++;
	}
	return (str);
}
