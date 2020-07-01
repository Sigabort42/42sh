#include "exec.h"
#include "env.h"
#include "lexer.h"
#include "error.h"
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>

static void	ft_check_pipe(t_tree *root, t_exec *exec, int direction)
{
	exec->type = EXEC_PIPE;
	ft_eval_tree(root->left, exec, FROM_LEFT);
	if (!(root->right->right) && direction == FROM_RIGHT)
		exec->type = EXEC_PIPE_LAST;
	ft_eval_tree(root->right, exec, FROM_RIGHT);
}

static void	ft_check_and(t_tree *root, t_exec *exec, int direction)
{
	if (root->left)
		ft_eval_tree(root->left, exec, direction);
	reset_fd(exec);
	ft_init_exec(exec);
	if (exec->last_ret == 0)
	{
		if (root->right)
			ft_eval_tree(root->right, exec, direction);
		reset_fd(exec);
		ft_init_exec(exec);
	}
}

static void	ft_check_or(t_tree *root, t_exec *exec, int direction)
{
	if (root->left)
		ft_eval_tree(root->left, exec, direction);
	reset_fd(exec);
	ft_init_exec(exec);
	if (exec->last_ret != 0)
	{
		if (root->right)
			ft_eval_tree(root->right, exec, direction);
		reset_fd(exec);
		ft_init_exec(exec);
	}
}

static void	ft_check_sc(t_tree *root, t_exec *exec, int direction)
{
	if (root->left)
	{
		ft_eval_tree(root->left, exec, direction);
		reset_fd(exec);
		ft_init_exec(exec);
	}
	if (root->right)
	{
		ft_eval_tree(root->right, exec, direction);
		reset_fd(exec);
		ft_init_exec(exec);
	}
}

void		ft_eval_tree(t_tree *root, t_exec *exec, int direction)
{
	if (direction == NO_DIRECTION)
	{
		if (root->node->id == ID_RED_RIGHT || root->node->id == ID_APPEND
				|| root->node->id == ID_RED_LEFT)
			direction = FROM_LEFT;
		else if (root->node->id == ID_PIPE)
			direction = FROM_RIGHT;
	}
	if (root->node->id == ID_SEMICOLON)
		ft_check_sc(root, exec, direction);
	else if (root->node->id == ID_AND)
		ft_check_and(root, exec, direction);
	else if (root->node->id == ID_OR)
		ft_check_or(root, exec, direction);
	else
		ft_check_file(root);
	if (root->node->id == ID_PIPE)
		ft_check_pipe(root, exec, direction);
	if (root->node->id == ID_WORD)
		ft_exec(root, exec);
}
