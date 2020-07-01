#include "env.h"
#include "../../libft/libft.h"
#include <stdlib.h>

static void	increase_shlvl(void)
{
	char	*tmp;
	int		shlvl;

	if (ft_getenv(g_env, "SHLVL"))
		shlvl = ft_atoi(ft_getenv(g_env, "SHLVL")->value) + 1;
	else
	{
		ft_setenv(&g_env, "SHLVL", "1", 0);
		return ;
	}
	tmp = ft_l_b((long long)shlvl, 10);
	ft_setenv(&g_env, "SHLVL", tmp, 1);
	free(tmp);
}

int			ft_init_env_from_tab(char **env)
{
	char	*tmp;
	int		i;

	i = 0;
	if (!env[0])
		ft_default_env();
	while (env[i])
	{
		tmp = ft_strsub(env[i], 0, ft_strchr(env[i], '=') - env[i]);
		ft_setenv(&g_env, tmp, ft_strchr(env[i], '=') + 1, 0);
		free(tmp);
		i++;
	}
	increase_shlvl();
	return (0);
}

char		**ft_copy_env_to_tab(t_env *list)
{
	char	**env;
	t_env	*tmp;
	int		i;

	i = 0;
	tmp = list;
	if (!(env = malloc(sizeof(char*) * (env_get_size(list) + 1))))
		return (NULL);
	while (tmp)
	{
		env[i] = ft_strnew(ft_strlen(tmp->name) + 1 + ft_strlen(tmp->value));
		ft_strcat(env[i], tmp->name);
		ft_strcat(env[i], "=");
		ft_strcat(env[i], tmp->value);
		i++;
		tmp = tmp->next;
	}
	env[i] = NULL;
	return (env);
}

char		**ft_copy_path(t_env *list)
{
	char	**path;
	t_env	*tmp;

	tmp = ft_getenv(list, "PATH");
	path = (tmp) ? ft_strsplit_charset(tmp->value, ":") : NULL;
	if (!path)
		return (NULL);
	else
		return (path);
}

t_env		*ft_duplicate_env(t_env *list)
{
	t_env	*tmp;
	t_env	*new;
	t_env	*begin;

	if (!list)
		return (NULL);
	tmp = list;
	new = env_create_elem(tmp->name, tmp->value);
	begin = new;
	if (!(tmp = tmp->next))
		return (begin);
	while (tmp->next)
	{
		new->next = env_create_elem(tmp->name, tmp->value);
		new->next->prev = new;
		tmp = tmp->next;
		new = new->next;
	}
	new->next = env_create_elem(tmp->name, tmp->value);
	new->next->prev = new;
	return (begin);
}
