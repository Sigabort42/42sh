#include "env.h"
#include "../../libft/libft.h"
#include <stdlib.h>

int		env_get_size(t_env *list)
{
	t_env	*tmp;
	int		size;

	size = 0;
	tmp = list;
	while (tmp)
	{
		tmp = tmp->next;
		size++;
	}
	return (size);
}

t_env	*env_create_elem(const char *name, const char *value)
{
	t_env	*elem;

	if (!(elem = malloc(sizeof(t_env))))
		return (NULL);
	elem->name = ft_strdup((char*)name);
	elem->value = ft_strdup((char*)value);
	elem->prev = NULL;
	elem->next = NULL;
	return (elem);
}

void	env_push_back(t_env **list, t_env *elem)
{
	t_env	*tmp;

	if ((*list) == NULL)
	{
		(*list) = elem;
		return ;
	}
	tmp = (*list);
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = elem;
	elem->prev = tmp;
}

void	flush_env(t_env **list)
{
	t_env	*tmp;
	t_env	*elem_tmp;

	tmp = *list;
	while (tmp)
	{
		elem_tmp = tmp->next;
		free(tmp->name);
		free(tmp->value);
		free(tmp);
		tmp = elem_tmp;
	}
	*list = NULL;
}
