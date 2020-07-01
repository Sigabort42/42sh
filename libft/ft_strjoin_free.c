#include "libft.h"

char		*ft_strjoin_free(char *s1, char *s2)
{
	char	*str;

	if (!s1 && !s2)
		return (NULL);
	if (!s1 && s2)
		return (ft_strdup(s2));
	else if (!s2 && s1)
		return (ft_strdup(s1));
	if (!(str = (char *)malloc(sizeof(char) * ft_strlen(s1) +
			ft_strlen(s2) + 1)))
		return (NULL);
	ft_strcpy(str, s1);
	ft_strcpy(str + ft_strlen(s1), s2);
	free(s1);
	free(s2);
	return (str);
}
