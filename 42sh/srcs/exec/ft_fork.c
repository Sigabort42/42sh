#include "exec.h"
#include "error.h"
#include "ft_signal.h"
#include <limits.h>
#include <signal.h>

static void	check_redir(t_process *prog, t_exec *exec)
{
	int		ret;
	t_redir	*red;

	red = prog->redir;
	ret = 0;
	if (red)
	{
		while (red)
		{
			ret = open_fd(red, exec);
			if (ret == EXEC_BAD_REDIR)
				prog->ret = EXEC_BAD_REDIR;
			if (red->id == ID_AG_RIGHT)
				dup2(red->right_fd, red->left_fd);
			red = red->next;
		}
	}
}

static void	delete_heredoc_temp(t_process *prog)
{
	t_redir	*red;

	red = prog->redir;
	if (red)
	{
		while (red)
		{
			if (red->id == ID_HEREDOC)
			{
				if (red->file)
					unlink(red->file);
			}
			red = red->next;
		}
	}
}

static void	fork_child(t_process *prog, t_exec *exec)
{
	if (exec->type == EXEC_PIPE || exec->type == EXEC_PIPE_LAST)
	{
		dup2(exec->pipe_link, 0);
		if (exec->type != EXEC_PIPE_LAST)
			dup2(exec->pipe_des[1], 1);
		close(exec->pipe_des[0]);
	}
	check_redir(prog, exec);
	if (prog->ret != EXEC_BAD_REDIR)
	{
		if (prog->ret != EXEC_OK && prog->builtin_id == EXEC_BUILTIN_NOT_FOUND)
			ft_usage_prog(prog->ret, prog->args[0]);
		if (prog->builtin_id != EXEC_BUILTIN_NOT_FOUND)
			exit((prog->ret = exec_builtin(&(prog->env_list), prog, exec)));
		if (execve(prog->command, prog->args, prog->env) == -1)
		{
			prog->ret = -1;
			exit(-1);
		}
	}
}

static void	fork_parent(t_process *prog, t_exec *exec)
{
	prog->ret = prog->ret;
	if (exec->type == EXEC_PIPE || exec->type == EXEC_PIPE_LAST)
	{
		if (exec->pipe_link != 0)
			close(exec->pipe_link);
		if (exec->type == EXEC_PIPE_LAST)
			exec->pipe_link = 0;
		else
			exec->pipe_link = exec->pipe_des[0];
		close(exec->pipe_des[1]);
	}
}

int			fork_program(t_process *prog, t_exec *exec)
{
	if (exec->type == EXEC_PIPE || exec->type == EXEC_PIPE_LAST)
		pipe(exec->pipe_des);
	prog->id = fork();
	if (prog->id == 0)
	{
		fork_child(prog, exec);
		exit(prog->ret);
	}
	if (prog->id > 0)
		fork_parent(prog, exec);
	ft_wait_id_push_back(exec, prog->id);
	delete_heredoc_temp(prog);
	return (prog->ret);
}
