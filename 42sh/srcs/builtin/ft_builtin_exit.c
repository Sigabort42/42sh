#include "builtin.h"
#include "../../libft/libft.h"
#include "error.h"
#include "exec.h"
#include <stdlib.h>
#include <stdio.h>

int	ft_builtin_exit(t_env **env, t_process *prog, t_exec *exec)
{
	char			**save;
	unsigned char	ret;

	save = prog->args;
	prog->args++;
	ret = 0;
	if (prog->args[0])
		ret = (unsigned char)ft_atoi(prog->args[0]);
	else
		ret = exec->last_ret;
	if (prog->args[0] && prog->args[1])
		return (ft_usage_exit(EXIT_TOO_MANY_ARG));
	history_write_session((*env)->shell);
	ft_freetab(((*env)->shell)->operators);
	ft_freetab(((*env)->shell)->tab_history);
	ft_freetab(((*env)->shell)->tab_session);
	ft_freetab(((*env)->shell)->init.evp);
	flush_env(&g_env);
	delete_program(&prog);
	exit(ret);
}
