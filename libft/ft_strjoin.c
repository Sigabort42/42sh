#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	if (s1 == 0 || s2 == 0)
		return (0);
	if ((str = (char *)malloc(sizeof(*str) *
ft_strlen(s1) + ft_strlen(s2) + 1)) == 0)
		return (0);
	while (s1[i])
		str[j++] = s1[i++];
	i = 0;
	while (s2[i])
		str[j++] = s2[i++];
	str[j] = 0;
	return (str);
}
