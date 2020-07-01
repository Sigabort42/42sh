#include "ft_signal.h"
#include "tree.h"
#include "env.h"
#include "exec.h"
#include "manage_line.h"
#include "main.h"
#include <term.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

void	exec_line(t_shell *shell, t_exec *exec)
{
	t_token	*list;
	t_tree	*root;

	ft_init_exec(exec);
	ft_init_termcap(shell);
	shell->buf = ft_manage_line(shell);
	puts("");
	if (!shell->buf || !ft_strlen(shell->buf))
		return ;
	ft_restore_termcap(&shell->tc);
	list = tokenizer(shell->buf);
	if (fusion_operator(&list) == 0)
	{
		root = new_tree();
		root->node = list;
		root->shell = shell;
		construct_tree(&root, 0);
		ft_eval_tree(root, exec, NO_DIRECTION);
		reset_fd(exec);
		free_tree(root);
	}
	else
		free_token_list(list);
}

int		main(int ac, char **av, char **env)
{
	t_exec	exec;
	t_shell	shell;

	(void)ac;
	(void)av;
	ft_init_env_from_tab(env);
	ft_init_shell(&shell, env);
	ft_init_history(&shell);
	ft_init_signal();
	ft_init_wait_id(&exec);
	exec.last_ret = 0;
	g_env->shell = &shell;
	while (42)
	{
		exec_line(&shell, &exec);
		free(shell.buf);
		close(shell.fd_history);
	}
	return (0);
}
