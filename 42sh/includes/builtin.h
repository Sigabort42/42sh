#ifndef BUILTIN_H
# define BUILTIN_H

# include "env.h"
# include "exec.h"

# define BUILTIN_LIST		"echo,cd,setenv,unsetenv,env,exit,history"

# define IS_OP(x, y)			((x & y) > 0)

# define ECHO_OP				"n"
# define ECHO_OP_N				1
# define CD_OP					"LP"
# define CD_OP_L				1
# define CD_OP_P				2

# define HIST_OP				"cdarnwps"

# define ENV_OP					"iu"
# define ENV_OP_I				1
# define ENV_OP_U				2

# define CD_APPEND_DIR			1
# define CD_TRUNCATE_DIR		2

# define HIST_OP_CLEAR			1
# define HIST_OP_DELOFFSET		2
# define HIST_OP_SESSTOFILE		4
# define HIST_OP_ADDFILE		8
# define HIST_OP_ADDUNREAD		16
# define HIST_OP_WRITE			32
# define HIST_OP_SUBSITUTE		64
# define HIST_OP_ADD			128

/*
**		builtin utils
*/
char				check_args(char ***args,
					int *options, const char *builtin_options);
int					option_less(t_env *list, char **dir);
void				set_pwd(t_env **list, char *path);
/*
**		builtins
*/
int					ft_builtin_cd(t_env **list, t_process *prog);
int					ft_builtin_echo(t_env *list, t_process *prog);
int					ft_builtin_env(t_env *list, t_process *prog, t_exec *exec);
int					ft_builtin_exit(t_env **env, t_process *prog, t_exec *exec);
int					ft_builtin_history(t_shell *shell, t_process *prog);
int					ft_builtin_setenv(t_env **list, t_process *prog);
int					ft_builtin_unsetenv(t_env **list, t_process *prog);

/*
**		builtin history
*/
char				**ft_filetotab(char *path);
void				history_delete_offset(t_shell *shell, int offset);
void				history_clear(t_shell *shell);
void				session_to_file(t_shell *shell, char *file);
void				history_add_file(t_shell *shell, char *file);
void				history_write_session(t_shell *shell);
void				history_write(t_shell *shell, char *file);
void				history_add_unread(t_shell *shell, char *file);
void				history_subsitution(char **args);
void				history_add(t_shell *shell, char **args);
void				history_print(t_shell *shell);
char				**str_to_tab(char *str);
char				**history_append(char **history, char *str);
int					ft_history_usage(char *list);

#endif
