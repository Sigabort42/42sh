#include "libft.h"

char	*ft_getword(char *str)
{
	int		len;

	len = 0;
	while (str[len] && !ft_isspace(str[len]))
		len++;
	return (ft_strndup(str, len, 0));
}
