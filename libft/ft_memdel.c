#include "libft.h"

void	ft_memdel(void **ap)
{
	free(*ap);
	*ap = 0;
}
