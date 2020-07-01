#include "builtin.h"
#include "../../libft/libft.h"
#include "error.h"
#include "exec.h"
#include <limits.h>
#include <unistd.h>

static void	modify_path(char *path, char *dir, int flag)
{
	char	*tmp;

	if (flag == CD_TRUNCATE_DIR)
	{
		tmp = ft_strrchr(path, '/');
		if (tmp)
			ft_memset(tmp, 0, ft_strlen(tmp));
		if (ft_strlen(path) == 0)
			ft_strcat(path, "/");
	}
	else if (flag == CD_APPEND_DIR)
	{
		if (path[ft_strlen(path) - 1] != '/')
			ft_strcat(path, "/");
		ft_strcat(path, dir);
	}
}

static void	get_pwd(t_env **list, char *path, char *dir, int flag_p)
{
	t_env	*pwd;
	char	pwd_path[PATH_MAX];

	ft_memset(pwd_path, 0, PATH_MAX);
	pwd = ft_getenv(*list, "PWD");
	if (flag_p == 0)
	{
		if (dir[0] == '/')
			ft_strcat(path, "/");
		else if (!pwd)
		{
			getcwd(pwd_path, PATH_MAX);
			ft_strcat(path, pwd_path);
		}
		else
			ft_strcat(path, pwd->value);
	}
	else if (flag_p == 1)
	{
		getcwd(pwd_path, PATH_MAX);
		ft_setenv(list, "PWD", pwd_path, 1);
	}
}

static int	check_valid_path(char *path, char *dir)
{
	t_stat	info;

	if (stat(path, &info) != 0)
		return (ft_usage_cd(CD_DIRECTORY_NOT_EXISTING, dir, 0));
	else if (!S_ISDIR(info.st_mode))
		return (ft_usage_cd(CD_NOT_A_DIRECTORY, dir, 0));
	else if (!(S_IXUSR & info.st_mode))
		return (ft_usage_cd(CD_PERMISSION_DENIED, dir, 0));
	return (0);
}

static int	get_current_dir(t_env **list, char *dir)
{
	char	path[PATH_MAX];
	char	**check;
	int		i;
	int		ret;

	ft_memset(path, 0, PATH_MAX);
	if (option_less(*list, &dir) != 0)
		return (ft_usage_cd(CD_OLDPWD_NOT_DEFINE, NULL, 0));
	get_pwd(list, path, dir, 0);
	i = 0;
	check = ft_strsplit(dir, '/');
	while (check[i])
	{
		if (ft_strcmp(check[i], "..") == 0)
			modify_path(path, NULL, CD_TRUNCATE_DIR);
		else if (ft_strcmp(check[i], ".") != 0)
			modify_path(path, check[i], CD_APPEND_DIR);
		i++;
	}
	free_tab(check);
	if ((ret = check_valid_path(path, dir)) != 0)
		return (ret);
	set_pwd(list, path);
	return (0);
}

int			ft_builtin_cd(t_env **list, t_process *prog)
{
	int				ret;
	int				options;

	options = 0;
	if ((ret = check_args(&(prog->args), &options, CD_OP)) != 0)
		return (ft_usage_cd(CD_OP_NOT_FOUND, NULL, ret));
	if (prog->args[0])
	{
		if ((ret = get_current_dir(list, prog->args[0])) != 0)
			return (ret);
	}
	else
	{
		if (ft_getenv(*list, "HOME"))
			set_pwd(list, ft_getenv(*list, "HOME")->value);
		else
			return (ft_usage_cd(CD_HOME_NOT_SET, NULL, 0));
	}
	if (chdir(ft_getenv(g_env, "PWD")->value) != 0)
		return (ft_usage_cd(CD_CHDIR_ERROR, NULL, 0));
	if (IS_OP(options, CD_OP_P))
		get_pwd(list, NULL, NULL, 1);
	return (0);
}
