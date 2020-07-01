#include "libft.h"
#include "error.h"
#include "builtin.h"

int	ft_usage_env(char ret, char *str, int flag)
{
	if (flag == ENV_CMD_NOT_FOUND)
		ft_printf("env: %s:   {fd}2command not found\n", str);
	else if (flag == ENV_OPT_NOT_FOUND)
	{
		ft_printf("env: {fd}2illegal option -- %c\n", ret);
		ft_printf("usage: {fd}2env [-%s] ", ENV_OP);
		ft_printf("[name=value ...] {fd}2[utility [argument ...]]\n");
	}
	else if (flag == ENV_SETENV_FAIL)
		ft_printf("env: setenv %s: {fd}2Invalid argument\n", str);
	return (flag);
}

int	ft_usage_setenv(int flag)
{
	if (flag == SETENV_TOO_MANY_ARG)
		ft_printf("setenv: {fd}2Too many arguments.\n");
	else if (flag == SETENV_NAME_CONTAINS_EQUAL)
	{
		ft_printf("setenv: {fd}2Variable name must ");
		ft_printf("contain {fd}2alphanumeric characters.\n");
	}
	else if (flag == SETENV_NAME_LETTER)
		ft_printf("setenv: {fd}2Variable name must begin with a letter.\n");
	else if (flag == SETENV_VALUE_BRACKET)
		ft_printf("setenv: {fd}2Unmatched \"\n");
	return (1);
}

int	ft_usage_cd(int flag, char *str, int ret)
{
	if (flag == CD_DIRECTORY_NOT_EXISTING)
		ft_printf("cd: %s: {fd}2No such file or directory.\n", str);
	else if (flag == CD_HOME_NOT_SET)
		ft_printf("cd: {fd}2No home directory.\n");
	else if (flag == CD_OP_NOT_FOUND)
	{
		ft_printf("cd: {fd}2illegal option -- %c\n", (char)ret);
		ft_printf("usage: {fd}2cd [-LP] [-] directory\n");
	}
	else if (flag == CD_CHDIR_ERROR)
		ft_printf("cd: {fd}2chdir error, PWD unchanged.\n");
	else if (flag == CD_NOT_A_DIRECTORY)
		ft_printf("cd: %s: {fd}2Not a directory.\n", str);
	else if (flag == CD_PERMISSION_DENIED)
		ft_printf("cd: %s: {fd}2Permission denied.\n", str);
	else if (flag == CD_OLDPWD_NOT_DEFINE)
		ft_printf("cd: {fd}2OLDPWD not set.\n");
	return (1);
}

int	ft_usage_exit(int flag)
{
	if (flag == EXIT_TOO_MANY_ARG)
		ft_printf("exit: {fd}2Too many arguments.\n");
	return (1);
}
