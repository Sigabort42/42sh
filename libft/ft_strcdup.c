#include "libft.h"

char		*ft_strcdup(char *s1, int c)
{
	int		i;
	char	*str;

	if (!s1)
		return (NULL);
	i = 0;
	while (s1[i] && s1[i] != c)
		i++;
	if (!(str = (char *)malloc(sizeof(char) * (i + 1))))
		return (NULL);
	ft_strncpy(str, s1, i);
	str[i] = '\0';
	return (str);
}
