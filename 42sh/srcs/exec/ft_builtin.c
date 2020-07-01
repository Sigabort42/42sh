#include "builtin.h"
#include "libft.h"
#include "exec.h"
#include "error.h"

int	check_builtin(char *name)
{
	char	**built;
	int		i;
	int		ret;

	i = 0;
	ret = EXEC_BUILTIN_NOT_FOUND;
	built = ft_strsplit_charset(BUILTIN_LIST, ",");
	while (built[i])
	{
		if (ft_strcmp(built[i], name) == 0)
			ret = i + 4;
		i++;
	}
	free_tab(built);
	return (ret);
}

int	exec_builtin(t_env **env, t_process *prog, t_exec *exec)
{
	if (prog->builtin_id == EXEC_BUILTIN_ECHO)
		prog->ret = ft_builtin_echo(*env, prog);
	else if (prog->builtin_id == EXEC_BUILTIN_CD)
		prog->ret = ft_builtin_cd(env, prog);
	else if (prog->builtin_id == EXEC_BUILTIN_SETENV)
		prog->ret = ft_builtin_setenv(env, prog);
	else if (prog->builtin_id == EXEC_BUILTIN_UNSETENV)
		prog->ret = ft_builtin_unsetenv(env, prog);
	else if (prog->builtin_id == EXEC_BUILTIN_ENV)
		prog->ret = ft_builtin_env(*env, prog, exec);
	else if (prog->builtin_id == EXEC_BUILTIN_EXIT)
		prog->ret = ft_builtin_exit(env, prog, exec);
	else if (prog->builtin_id == EXEC_BUILTIN_HISTORY)
		prog->ret = ft_builtin_history((*env)->shell, prog);
	return (prog->ret);
}
