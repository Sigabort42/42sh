#include "libft.h"
#include "error.h"
#include "builtin.h"

int	ft_usage_prog(int flag, char *str)
{
	if (flag == EXEC_CMD_NOT_FOUND)
	{
		ft_putstr_fd("42sh: command not found: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd("\n", 2);
	}
	return (1);
}

int	ft_usage_file(int flag, char *str)
{
	if (flag == FILE_NOT_FOUND)
	{
		ft_putstr_fd("42sh: no such file or directory: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd("\n", 2);
	}
	if (flag == FILE_NOT_ACCESS)
	{
		ft_putstr_fd("42sh: permission denied: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd("\n", 2);
	}
	if (flag == FILE_IS_DIR)
	{
		ft_putstr_fd("42sh: is a folder: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd("\n", 2);
	}
	return (1);
}
