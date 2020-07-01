#include "completion.h"

void		my_free_lst(t_file *lst)
{
	t_file	*l;

	if (!(lst = get_lst_end(lst, 0)))
		return ;
	while (lst)
	{
		l = lst->next;
		free(lst->name);
		lst->name = NULL;
		free(lst);
		lst = l;
	}
}

char		**lst_to_tab(char **tab, t_file *first)
{
	int		len;
	t_file	*l;

	l = first;
	len = 0;
	while (l)
	{
		len++;
		l = l->next;
	}
	if (!(tab = (char**)ft_memalloc(sizeof(char*) * (len + 1))))
		return (NULL);
	tab[len--] = NULL;
	l = first;
	len = 0;
	while (l)
	{
		if (!(tab[len++] = ft_strdup(l->name)))
			return (NULL);
		l = l->next;
	}
	return (tab);
}

t_file		*my_lstnew(char *name, int i)
{
	t_file	*lst;

	if (!(lst = (t_file*)ft_memalloc(sizeof(t_file))))
		return (NULL);
	lst->name = ft_strdup(name);
	lst->isdir = i;
	lst->next = NULL;
	lst->prev = NULL;
	return (lst);
}

void		my_lst_add(t_file *lst, t_file *add)
{
	if (!lst || !add)
		return ;
	lst->next = add;
	add->prev = lst;
}

t_file		*get_lst_end(t_file *lst, int i)
{
	if (lst == NULL)
		return (NULL);
	if (i)
	{
		while (lst->next)
			lst = lst->next;
	}
	else
	{
		while (lst->prev)
			lst = lst->prev;
	}
	return (lst);
}
