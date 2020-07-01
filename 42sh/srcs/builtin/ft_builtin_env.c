#include "builtin.h"
#include "libft.h"
#include "error.h"
#include "exec.h"
#include <stdlib.h>

static int	check_setenv(t_env **list, char *str)
{
	char	*tmp;
	int		ret;

	ret = 0;
	tmp = ft_strsub(str, 0, ft_strchr(str, '=') - str);
	ret = ft_setenv(list, tmp, ft_strchr(str, '=') + 1, 1);
	free(tmp);
	return (ret);
}

static int	env_exec_command(t_env **list, t_exec *exec, char **args, int i)
{
	t_process	*prog_tmp;
	int			ret;

	ret = 0;
	if (!(prog_tmp = malloc(sizeof(t_process))))
		return (-1);
	prog_tmp->id = 0;
	prog_tmp->builtin_id = EXEC_BUILTIN_NOT_FOUND;
	prog_tmp->args = duplicate_tab(args);
	prog_tmp->first_arg = prog_tmp->args;
	prog_tmp->env = ft_copy_env_to_tab(*list);
	prog_tmp->env_list = *list;
	prog_tmp->redir = NULL;
	prog_tmp->ret = 0;
	prog_tmp->args += i;
	prog_tmp->ret = check_command(prog_tmp);
	ret = fork_program(prog_tmp, exec);
	exec->last_ret = prog_tmp->ret;
	delete_program(&prog_tmp);
	return (ret);
}

static char	valid_args(t_env **list, t_process *prog, t_exec *exec)
{
	int	i;
	int	ret;

	i = 0;
	ret = ENV_CMD_END;
	while (prog->args[i])
	{
		if (ft_strchr(prog->args[i], '='))
		{
			prog->ret = check_setenv(list, prog->args[i]);
			if (prog->ret != 0)
				return (ft_usage_env(prog->ret, prog->args[i],
							ENV_SETENV_FAIL));
		}
		else
		{
			env_exec_command(list, exec, prog->args, i);
			return (ENV_CMD_END);
		}
		i++;
	}
	return (0);
}

int			ft_builtin_env(t_env *list, t_process *prog, t_exec *exec)
{
	int		options;
	char	ret;
	t_env	*copy_env;

	copy_env = ft_duplicate_env(list);
	options = 0;
	ret = 0;
	if ((ret = check_args(&(prog->args), &options, ENV_OP)) > 0)
		return (ft_usage_env(ret, NULL, ENV_OPT_NOT_FOUND));
	if (IS_OP(options, ENV_OP_I))
		flush_env(&copy_env);
	ret = valid_args(&copy_env, prog, exec);
	if (ret == 0)
		ft_print_env(copy_env);
	flush_env(&copy_env);
	return (ret);
}
