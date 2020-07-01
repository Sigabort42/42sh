#include "builtin.h"
#include "../../libft/libft.h"
#include "error.h"
#include "exec.h"
#include <stdlib.h>

int		ft_unsetenv(t_env **list, const char *name)
{
	t_env	*tmp;

	if (ft_strchr(name, '='))
		return (-1);
	tmp = ft_getenv((*list), name);
	if (tmp)
	{
		if ((*list) == tmp)
			(*list) = (*list)->next;
		if (tmp->prev)
			tmp->prev->next = (tmp->next) ? tmp->next : NULL;
		if (tmp->next)
			tmp->next->prev = (tmp->prev) ? tmp->prev : NULL;
		free(tmp->name);
		free(tmp->value);
		free(tmp);
	}
	return (0);
}

int		ft_builtin_unsetenv(t_env **list, t_process *prog)
{
	int	i;

	i = 0;
	prog->args++;
	while (prog->args[i])
	{
		ft_unsetenv(list, prog->args[i]);
		i++;
	}
	return (0);
}
