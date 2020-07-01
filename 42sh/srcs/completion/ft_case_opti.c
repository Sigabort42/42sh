#include "completion.h"

static int		check_prev(t_token *l)
{
	if (l->id == 0 || l->id == 1 || l->id == 4 || l->id == 5 || l->id == 6)
		return (PRINT_CMD);
	else if (l->id == 2 || l->id == 3)
		return (PRINT_FILE);
	else if (l->id == 11)
	{
		if (l->prev && l->prev->prev && l->prev->id == 12
			&& l->prev->prev->id == 11)
		{
			if (l->content[ft_strlen(l->content) - 1] == '/')
				return (PRINT_NEXT_FILE);
			return (COMPLETE_FILE);
		}
		return (COMPLETE_CMD);
	}
	while (l->prev)
		l = l->prev;
	return (-1);
}

int				find_case(t_token *first)
{
	t_token		*tmp;

	tmp = first;
	if (tmp->id == 12)
		tmp = tmp->next;
	if (tmp->id == 13)
		return (PRINT_CMD);
	while (tmp->next && tmp->id != 13)
		tmp = tmp->next;
	if (tmp->prev && tmp->prev->id == 12 && tmp->prev->prev
		&& tmp->prev->prev->id == 11)
		return (PRINT_FILE);
	if (tmp->prev && tmp->prev->id == 12)
		tmp = tmp->prev;
	return (check_prev(tmp->prev));
}

int				test_for_i(t_file *lst, int i)
{
	while (lst->next)
	{
		if (lst->name[i] != lst->next->name[i])
			return (0);
		lst = lst->next;
	}
	return (1);
}

t_file			*opti_ret(char *str, t_file *lst)
{
	int		i;
	char	*tmpp;

	i = (str) ? ft_strlen(str) - 1 : 0;
	if (!lst)
		return (NULL);
	if (!lst->next)
		return (lst);
	while (test_for_i(lst, i))
		i++;
	if (i <= 1 || i == (int)((str) ? ft_strlen(str) - 1 : 0))
		return (lst);
	tmpp = ft_strdup(lst->name);
	tmpp[i] = '\0';
	if (!str || (ft_strncmp(tmpp, str, ft_strlen(str) - 1) == 0))
	{
		my_free_lst(lst);
		lst = my_lstnew(tmpp, 0);
	}
	free(tmpp);
	return (lst);
}
