#ifndef MANAGE_LINE_H
# define MANAGE_LINE_H
# include "../../libft/libft.h"
# include "lexer.h"
# include "tree.h"
# include <sys/ioctl.h>
# include <termios.h>
# include <unistd.h>
# include <curses.h>

# define OPERATORS		"&&:&:||:|:\\"

# define CTRL_C			8
# define CTRL_D			5

typedef struct			s_init
{
	char				**evp;
	char				**path_tab;
	t_token				*first;
	t_token				*last;
	t_tree				*root;
}						t_init;

typedef struct			s_termcap
{
	char				*dc;
	char				*cs;
	char				*me;
	char				*cm;
	char				*im;
	char				*le;
	char				*nd;
	char				*ce;
	char				*le_m;
	char				*ri_m;
	int					co;
	struct termios		tios;
	struct termios		shell_tmodes;
	struct winsize		wsize;
}						t_termcap;

typedef struct			s_shell
{
	t_termcap			tc;
	t_init				init;
	t_tree				ast;
	int					csr;
	int					row;
	int					col;
	int					f_len;
	int					line;
	int					line_total;
	int					heredoc;
	int					isline;
	int					fd_tty;
	int					fd_history;
	int					csr_copy;
	int					quote;
	int					bang_modif;
	int					line_session;
	int					shell_terminal;
	int					shell_is_interactive;
	int					fg;
	int					octet_hist;
	pid_t				shell_pgid;
	char				*states;
	char				*type_term;
	char				**operators;
	char				**tab_history;
	char				**tab_session;
	char				*chemin_history;
	char				*actual_line;
	char				*buf;
	char				*buf_mem;
	char				*format;
}						t_shell;

typedef struct			s_bang
{
	int					i;
	char				*tmp;
	char				*line;
}						t_bang;

char					**g_signal;

int						ft_verif_c(t_shell *shell, char *c, int *csr,
char **buf);
void					ft_refresh_line(t_shell *shell, char *line, int csr);
char					*ft_manage_line(t_shell *shell);
void					ft_move_word(t_shell *shell, const char *s,
int *csr, int f);
void					ft_init_manage(t_shell *shell);
void					ft_move_line_up_down(char *c, int *csr, t_shell *shell);
void					ft_moveword_home_end_history(char **buf,
char *c, int *csr,
t_shell *shell);
int						ft_moveone_cut_and_delete(char **buf, char *c,
int *csr, t_shell *shell);
int						ft_search_var_env(char **evp, char *varia);
char					**ft_copy_evp(char **evp);
void					history_push(t_shell *shell, char *str);
void					ft_freetab(char **to_free);
char					**ft_str2join_free(char **tab1, char **tab2, int free);
int						ft_tablen(char **str2);
int						ft_count_line(char *chemin);
void					ft_strappend(char **str, char c);

char					*get_name(char *str);
int						manage_bang(t_shell *shell);
int						bang_string(t_shell *shell, t_bang *bang);
int						bang_n(t_shell *shell, t_bang *bang);
int						bang_previous(t_shell *shell, t_bang *bang);

void					print_word(char *str);
void					ft_check_quote(t_shell *shell, char **str, char **ev);

void					ft_restore_termcap(t_termcap *tc);

void					check_backslash(t_shell *shell, char **line);
int						check_end_line(t_shell *shell, char **to_append, int s);
void					check_inhib_operators(t_shell *shell, char **str);
int						line_end(t_shell *shell, char *str);
void					check_heredoc(t_shell *shell, char **str);
int						increment_heredoc_tmpfile(t_shell *shell, char **path);
char					**get_delimiters(char *str);
void					delete_n_files(char **all_paths, int n);
void					suppr_backslash(t_shell *shell, char **line);
void					refresh_line(t_shell *shell);
int						check_ret(t_shell *shell, int ret, int *csr);
int						ft_complete_line2(t_shell *shell, int *ret);
int						ft_complete_line(t_shell *shell);
void					change_tield_by_home(t_shell *shell, char **line);
void					ft_check_line(t_shell *shell);
void					replace_var_env(t_shell *shell, char **str,
char **ev, int *i);
void					change_var_env(t_shell *shell, char **str, char **ev);

#endif
