#include "libft.h"
#include "exec.h"
#include "error.h"

int			ft_usage_redir(int fd)
{
	ft_putnbr_fd(fd, 2);
	ft_putstr_fd(": bad file descriptor\n", 2);
	return (EXEC_BAD_REDIR);
}

int			open_fd(t_redir *redir, t_exec *exec)
{
	int		fd;

	fd = 0;
	if (redir->right_fd != -1)
	{
		if (redir->left_fd >= 0)
			exec->save_fd[redir->left_fd] = dup(redir->left_fd);
		if (redir->left_fd == REDIR_AG_1_2)
		{
			exec->save_fd[1] = dup(1);
			exec->save_fd[2] = dup(2);
			fd = dup2(redir->right_fd, 1);
			fd = dup2(redir->right_fd, 2);
		}
		else if (redir->right_fd == REDIR_AG_CLOSE)
			close(redir->left_fd);
		else
			fd = dup2(redir->right_fd, redir->left_fd);
		if (fd == -1)
			return (ft_usage_redir(fd));
	}
	else
		return (EXEC_BAD_REDIR);
	return (0);
}

void		reset_fd(t_exec *exec)
{
	int	i;

	i = 0;
	while (i < OPEN_MAX)
	{
		if (exec->save_fd[i] != -1)
		{
			dup2(exec->save_fd[i], i);
			close(exec->save_fd[i]);
		}
		i++;
	}
	if (exec->pipe_des[0] != 0)
		close(exec->pipe_des[0]);
	if (exec->pipe_des[1] != 0)
		close(exec->pipe_des[1]);
}
