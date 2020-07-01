#include "exec.h"
#include "error.h"

t_process	*new_program(t_tree *root)
{
	t_process	*elem;

	if (!(elem = malloc(sizeof(t_process))))
		return (NULL);
	elem->id = 0;
	elem->builtin_id = -1;
	elem->args = ft_strsplit_token(root->node->content, " \n\t");
	remove_quotes_args(elem->args);
	elem->first_arg = elem->args;
	elem->env = ft_copy_env_to_tab(g_env);
	elem->env_list = g_env;
	elem->redir = root->node->redir;
	elem->ret = 0;
	return (elem);
}

int			check_program(t_process *prog)
{
	if ((prog->builtin_id = check_builtin(prog->args[0])) !=
			EXEC_BUILTIN_NOT_FOUND)
		return (prog->builtin_id);
	if ((prog->ret = check_command(prog)) != EXEC_OK)
		return (prog->ret);
	return (prog->ret);
}

int			execute_program(t_process *prog, t_exec *exec)
{
	int		ret;

	ret = check_program(prog);
	prog->ret = ret;
	if (prog->builtin_id != EXEC_BUILTIN_NOT_FOUND
			&& exec->type == EXEC_FORK && prog->redir == NULL)
		ret = exec_builtin(&(prog->env_list), prog, exec);
	else
		ret = fork_program(prog, exec);
	return (ret);
}

void		delete_program(t_process **prog)
{
	if ((*prog)->first_arg)
	{
		(*prog)->args = (*prog)->first_arg;
		free_tab((*prog)->args);
		(*prog)->first_arg = NULL;
		(*prog)->args = NULL;
	}
	if ((*prog)->env)
	{
		free_tab((*prog)->env);
		(*prog)->env = NULL;
	}
	free(*prog);
	*prog = NULL;
}
