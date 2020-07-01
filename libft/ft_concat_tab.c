#include "libft.h"

char		*ft_concat_tab(char **to_str, char *delim)
{
	int		i;
	char	*tmp;
	char	*new_str;

	i = 0;
	new_str = ft_strnew(0);
	while (to_str[i])
	{
		tmp = ft_strjoin(new_str, to_str[i++]);
		if (to_str[i])
			tmp = ft_strjoin_free(tmp, ft_strdup(delim));
		free(new_str);
		new_str = ft_strdup(tmp);
		free(tmp);
	}
	return (new_str);
}
