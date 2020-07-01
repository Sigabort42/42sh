#include "libft.h"
#include <limits.h>
#include <stdlib.h>

char	*remove_quotes(char *str)
{
	char	token[LINE_MAX];
	int		i;

	i = 0;
	ft_memset(token, 0, LINE_MAX);
	while (str[i])
	{
		if (str[i] != '\"' && str[i] != '\'')
			ft_strncat(token, &str[i], 1);
		i++;
	}
	if (token[0] != 0 && ft_strlen(str) != ft_strlen(token))
	{
		free(str);
		return (ft_strdup(token));
	}
	return (str);
}

void	remove_quotes_args(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		tab[i] = remove_quotes(tab[i]);
		i++;
	}
}
