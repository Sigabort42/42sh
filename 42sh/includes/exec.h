#ifndef EXEC_H
# define EXEC_H

# include "env.h"
# include "tree.h"
# include <limits.h>
# include <termios.h>

# define EXEC_FORK				0
# define EXEC_PIPE				1
# define EXEC_PIPE_LAST			2

# define NO_DIRECTION			0
# define FROM_LEFT				1
# define FROM_RIGHT				2

typedef struct			s_exec
{
	int					type;
	int					save_fd[OPEN_MAX];
	int					pipe_link;
	int					pipe_des[2];
	int					last_ret;
	pid_t				wait_id[CHILD_MAX];
}						t_exec;

typedef struct			s_process
{
	pid_t				id;
	int					builtin_id;
	char				command[PATH_MAX];
	char				**args;
	char				**first_arg;
	char				**env;
	char				completed;
	char				stopped;
	t_env				*env_list;
	t_redir				*redir;
	int					ret;
	int					status;
	struct s_process	*next;
}						t_process;

typedef struct			s_job
{
	char				*command;
	t_process			*first_process;
	pid_t				pgid;
	char				notified;
	int					stdin;
	int					stdout;
	int					stderr;
	struct termios		tmodes;
	struct s_job		*next;
}						t_job;

t_job					*g_first_job;
/*
**		manage args
*/
void					free_tab(char **tab);
char					**duplicate_tab(char **args);
void					delete_options_unused(char ***args, int index);
/*
**		struct exec
*/
void					ft_init_wait_id(t_exec *exec);
void					ft_init_exec(t_exec *exec);
void					ft_wait_id_push_back(t_exec *exec, pid_t id);
void					ft_exec_wait_id(t_exec *exec);
/*
**		struct: program
*/
t_process				*new_program(t_tree *root);
int						execute_program(t_process *prog, t_exec *exec);
int						fork_program(t_process *prog, t_exec *exec);
void					delete_program(t_process **prog);
/*
**		check builtin & executables
*/
int						check_builtin(char *name);
int						exec_builtin(t_env **env, t_process *prog,
t_exec *exec);
int						check_command(t_process *prog);
/*
**		execution
*/
int						ft_exec(t_tree *root, t_exec *exec);
int						ft_pipe(t_tree *root, t_exec *exec, int direction);
/*
**		tree browsing
*/
void					ft_eval_tree(t_tree *root, t_exec *exec, int direction);
/*
**		manage fd & files
*/
void					ft_check_file(t_tree *root);
int						open_fd(t_redir *redir, t_exec *exec);
void					reset_fd(t_exec *exec);

#endif
