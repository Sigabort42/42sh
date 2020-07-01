#include "completion.h"

char	*find_env(char **env, const char *need)
{
	int		i;

	i = -1;
	while (need && env && env[++i])
		if (ft_strncmp(env[i], need, ft_strlen(need)) == 0)
			return (ft_strdup((ft_strstr(env[i], "/"))));
	return (NULL);
}

void	ft_tabdel(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		ft_strdel(&tab[i++]);
	free(tab);
	tab = NULL;
}

void	tab_to_str(char **src, char **dst)
{
	int		len;
	int		i;

	i = 0;
	len = ft_tablen(src);
	while (src[i])
		len += ft_strlen(src[i++]);
	if (!(*dst = (char*)ft_memalloc(sizeof(char) * len + 1)))
		return ;
	(*dst)[len] = '\0';
	i = 0;
	while (src[i])
		ft_strcat(ft_strcat(*dst, "/"), src[i++]);
}

int		ft_is_dir(char *pwd)
{
	struct stat		info;

	if (lstat(pwd, &info) == -1)
		return (0);
	if (S_ISDIR(info.st_mode))
		return (1);
	return (0);
}

void	free_token(t_token *list)
{
	t_token	*tmp;

	while (list->next)
	{
		tmp = list;
		list = list->next;
		free_single_token(tmp);
	}
}
