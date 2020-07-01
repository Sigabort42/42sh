#include "completion.h"

static t_file		*read_dir(DIR *dirp, char *cmp, int len, char *pwd)
{
	struct dirent	*dp;
	t_file			*stt;
	char			path[PATH_MAX];

	stt = NULL;
	while ((dp = readdir(dirp)))
		if ((cmp && ft_strncmp(cmp, dp->d_name, len) == 0) || !cmp)
		{
			if (ft_strcmp(dp->d_name, "..") != 0
				&& ft_strcmp(dp->d_name, ".") != 0)
			{
				ft_bzero(path, PATH_MAX);
				ft_strcat(path, pwd);
				ft_strcat(ft_strcat(path, "/"), dp->d_name);
				if (stt)
					my_lst_add(get_lst_end(stt, 1), my_lstnew(dp->d_name,
						ft_is_dir(path)));
				else
					stt = my_lstnew(dp->d_name, ft_is_dir(path));
			}
		}
	return (stt);
}

static void			check_pwd_while(t_comp *comp, char *pwd, char *tab)
{
	char			*tmpp;
	char			*tmp;

	if (ft_strcmp(tab, "..") == 0)
	{
		tmpp = ft_strrchr(pwd, '/');
		ft_bzero(tmpp, ft_strlen(tmpp));
	}
	else if (ft_strcmp(tab, ".") != 0)
	{
		tmp = ft_strjoin(pwd, "/");
		tmpp = ft_strjoin(tmp, tab);
		free(tmp);
		if (ft_is_dir(tmpp))
			ft_strcat(ft_strcat(pwd, "/"), tab);
		else
			ft_strcat(ft_strcat(comp->start, tab), "/");
		free(tmpp);
	}
}

static int			check_pwd(t_comp *comp, char *pwd)
{
	char			**tab;
	int				i;

	i = -1;
	if (comp->start == NULL)
		return (1);
	if (!(tab = ft_strsplit(comp->start, '/')))
		return (-2);
	free(comp->start);
	if (!(comp->start = ft_strnew(PATH_MAX)))
		return (-3);
	while (tab[++i])
		check_pwd_while(comp, pwd, tab[i]);
	if (ft_strlen(comp->start) == 0)
	{
		free(comp->start);
		comp->start = NULL;
	}
	ft_tabdel(tab);
	return (1);
}

t_file				*do_it_file(t_comp *comp, char **env)
{
	char			*path;
	char			*pwd;
	t_file			*lst;
	DIR				*dirp;

	lst = NULL;
	if ((pwd = ft_strnew(PATH_MAX)))
	{
		if ((path = find_env(env, "PWD")))
		{
			ft_strcat(pwd, path);
			if (check_pwd(comp, pwd) != -1)
			{
				if ((dirp = opendir(pwd)))
				{
					lst = read_dir(dirp, comp->start,
						ft_strlen(comp->start) - 1, pwd);
					closedir(dirp);
				}
			}
			free(path);
		}
		free(pwd);
	}
	return (lst);
}
