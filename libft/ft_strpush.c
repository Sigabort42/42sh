#include "libft.h"

void	ft_strpush(char **str, char *in, int start)
{
	char	*new;

	new = ft_strnew(ft_strlen(*str) + ft_strlen(in) + 1);
	ft_strncpy(new, *str, start);
	ft_strcpy(new + start, in);
	ft_strcpy(new + start + ft_strlen(in), *str + start);
	ft_strdel(str);
	*str = new;
}
