#include "libft.h"

int			ft_tablen(char **str2)
{
	int	len;

	len = 0;
	while (str2[len])
		len++;
	return (len);
}
