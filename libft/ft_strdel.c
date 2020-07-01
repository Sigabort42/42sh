#include "libft.h"

void	ft_strdel(char **as)
{
	if (as == 0)
		return ;
	if (*as == 0)
		return ;
	free(*as);
	*as = 0;
}
