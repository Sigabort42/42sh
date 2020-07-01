#include "env.h"
#include "../../libft/libft.h"
#include <limits.h>
#include <unistd.h>

void	ft_print_env(t_env *list)
{
	t_env	*tmp;

	tmp = list;
	while (tmp)
	{
		ft_putstr(tmp->name);
		ft_putstr("=");
		ft_putendl(tmp->value);
		tmp = tmp->next;
	}
}

int		ft_default_env(void)
{
	char	cwd[PATH_MAX];

	ft_memset(cwd, 0, PATH_MAX);
	if (!getcwd(cwd, PATH_MAX))
		return (-1);
	ft_setenv(&g_env, "PWD", cwd, 0);
	ft_setenv(&g_env, "PATH", "/usr/bin:/bin", 0);
	ft_setenv(&g_env, "SHLVL", "1", 0);
	return (0);
}

t_env	*ft_getenv(t_env *list, const char *name)
{
	t_env	*tmp;

	tmp = list;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, name) == 0)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}
