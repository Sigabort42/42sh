#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	while (*alst != NULL)
	{
		del((*(alst))->content, (*(alst))->content_size);
		free(*alst);
		*alst = (*(alst))->next;
	}
}
