#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(t_list *elem))
{
	t_list	*tmp;

	tmp = lst;
	while (tmp != 0)
	{
		f(tmp);
		tmp = tmp->next;
	}
}
