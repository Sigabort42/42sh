#include "libft.h"

size_t		ft_lstcount(t_list *lst)
{
	t_list	*tmp;
	size_t	i;

	i = 0;
	tmp = lst;
	while (tmp != 0)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}
