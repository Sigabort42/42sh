#include "ft_signal.h"
#include "exec.h"
#include "env.h"
#include "lexer.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int		ft_exec(t_tree *root, t_exec *exec)
{
	int			ret;
	t_process	*prog;

	prog = new_program(root);
	ret = execute_program(prog, exec);
	delete_program(&prog);
	return (ret);
}

void	ft_init_exec(t_exec *exec)
{
	int	i;

	i = 0;
	exec->type = EXEC_FORK;
	while (i < OPEN_MAX)
	{
		exec->save_fd[i] = -1;
		i++;
	}
	ft_exec_wait_id(exec);
	ft_init_wait_id(exec);
	exec->pipe_des[0] = 0;
	exec->pipe_des[1] = 0;
	exec->pipe_link = 0;
}

void	ft_wait_id_push_back(t_exec *exec, pid_t id)
{
	int	i;

	i = 0;
	while (exec->wait_id[i] != -1 && i < CHILD_MAX)
		i++;
	exec->wait_id[i] = id;
}

void	ft_exec_wait_id(t_exec *exec)
{
	int	i;

	i = 0;
	while (i < CHILD_MAX)
	{
		if (exec->wait_id[i] != -1)
		{
			waitpid(exec->wait_id[i], &exec->last_ret, WUNTRACED);
			if (WIFSIGNALED(exec->last_ret))
				ft_print_signal_child(WTERMSIG(exec->last_ret),
					exec->wait_id[i]);
		}
		i++;
	}
	exec->last_ret = WEXITSTATUS(exec->last_ret);
}

void	ft_init_wait_id(t_exec *exec)
{
	int	i;

	i = 0;
	while (i < CHILD_MAX)
	{
		exec->wait_id[i] = -1;
		i++;
	}
}
