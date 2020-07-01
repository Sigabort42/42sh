#include "libft.h"

void	ft_lstpushback(t_list **lst, t_list *elem)
{
	t_list	*tmp;

	tmp = *lst;
	if (!lst)
		return ;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = elem;
}
