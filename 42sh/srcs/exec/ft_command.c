#include "exec.h"
#include "../../libft/libft.h"
#include "builtin.h"
#include "error.h"
#include <unistd.h>
#include <limits.h>
#include <stdlib.h>

static int	check_rights(char *command)
{
	t_stat	info;
	int		ret;

	if ((ret = lstat(command, &info)) != 0)
		return (EXEC_CMD_NOT_FOUND);
	if ((S_IXGRP & info.st_mode) && (S_IXUSR & info.st_mode)
		&& (S_IXOTH & info.st_mode))
		return (EXEC_OK);
	else
		return (EXEC_PATH_NO_RIGHTS);
	return (EXEC_OK);
}

int			check_command(t_process *prog)
{
	int		i;
	int		ret;
	char	**path;

	i = 0;
	path = ft_copy_path(prog->env_list);
	ft_memset(prog->command, 0, PATH_MAX);
	if (!path)
		ft_strcat(prog->command, prog->args[0]);
	if (!path)
		return ((ret = check_rights(prog->command)));
	while (path[i])
	{
		ft_memset(prog->command, 0, PATH_MAX);
		if ((ret = check_rights(prog->args[0])) != 0)
		{
			ft_strcat(prog->command, path[i++]);
			ft_strcat(prog->command, "/");
		}
		ft_strcat(prog->command, prog->args[0]);
		if ((ret = check_rights(prog->command)) == 0)
			break ;
	}
	free_tab(path);
	return (ret);
}
