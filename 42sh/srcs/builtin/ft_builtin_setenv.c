#include "builtin.h"
#include "../../libft/libft.h"
#include "error.h"
#include <stdlib.h>

int			ft_setenv(t_env **list, const char *name,
			const char *value, int overwrite)
{
	t_env	*tmp;
	t_env	*elem;

	if (!ft_isalpha(name[0]))
		return (SETENV_NAME_LETTER);
	if (ft_strchr(name, '='))
		return (SETENV_NAME_CONTAINS_EQUAL);
	tmp = ft_getenv(*list, name);
	if (tmp)
	{
		if (overwrite <= 0)
			return (0);
		free(tmp->value);
		tmp->value = ft_strdup((char*)((value) ? value : ""));
		return (0);
	}
	elem = env_create_elem(name, (value) ? value : "");
	env_push_back(list, elem);
	return (0);
}

int			ft_builtin_setenv(t_env **list, t_process *prog)
{
	int	i;
	int	ret;

	i = 0;
	prog->args++;
	while (prog->args[i])
		i++;
	if (i > 2)
		return (ft_usage_setenv(SETENV_TOO_MANY_ARG));
	if (i == 0)
	{
		ft_print_env(*list);
		return (0);
	}
	ret = ft_setenv(list, prog->args[0], prog->args[1], 1);
	if (ret != 0)
		return (ft_usage_setenv(ret));
	return (0);
}
