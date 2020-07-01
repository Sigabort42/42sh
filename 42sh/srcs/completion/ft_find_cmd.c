#include "completion.h"

static t_file	*read_dir(DIR *dirp, char *cmp, int len, char *pwd)
{
	struct dirent	*dp;
	t_file			*stt;
	char			path[PATH_MAX];

	stt = NULL;
	while ((dp = readdir(dirp)))
		if ((cmp && ft_strncmp(cmp, dp->d_name, len) == 0) || !cmp)
			if (ft_strcmp(dp->d_name, ".") != 0
				&& ft_strcmp(dp->d_name, "..") != 0)
			{
				ft_bzero(path, PATH_MAX);
				ft_strcat(path, pwd);
				ft_strcat(ft_strcat(path, "/"), dp->d_name);
				if (!ft_is_dir(path))
				{
					if (stt)
						my_lst_add(get_lst_end(stt, 1),
							my_lstnew(dp->d_name, 0));
					else
						stt = my_lstnew(dp->d_name, 0);
				}
			}
	return (get_lst_end(stt, 0));
}

static t_file	*browse_path(char *start, char **tab)
{
	int		i;
	t_file	*stt;
	t_file	*new;
	DIR		*dirp;

	i = 0;
	stt = NULL;
	while (tab[i])
	{
		if (!(dirp = opendir(tab[i])))
			i++;
		else
		{
			if ((new = read_dir(dirp, start, ft_strlen(start), tab[i++])))
			{
				if (stt)
					my_lst_add(get_lst_end(stt, 1), new);
				else
					stt = new;
			}
			closedir(dirp);
		}
	}
	return (stt);
}

t_file			*do_it_cmd(char *start, char **env)
{
	char	*tmp;
	t_file	*lst;
	char	**tab;

	if (!(tmp = find_env(env, "PATH")))
		return (NULL);
	if (!(tab = ft_strsplit(tmp, ':')))
		return (NULL);
	lst = browse_path(start, tab);
	ft_tabdel(tab);
	free(tmp);
	return (lst);
}
