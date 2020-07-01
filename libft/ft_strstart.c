#include "libft.h"

int		ft_strstart(char *str, char *start)
{
	if (ft_strncmp(str, start, ft_strlen(start)) != 0)
		return (0);
	return (1);
}
