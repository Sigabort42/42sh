#include "libft.h"

void	ft_strcut(char **str, int start, int len)
{
	char	*new;

	new = ft_strnew(ft_strlen(*str) - len + 1);
	ft_strncpy(new, *str, start);
	ft_strcpy(new + start, *str + start + len);
	ft_strdel(str);
	*str = new;
}
