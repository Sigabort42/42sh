#ifndef COMPLETION_H
# define COMPLETION_H

# include "manage_line.h"
# include "env.h"
# include <dirent.h>

# define COMPLETE_CMD		1
# define PRINT_CMD			2
# define COMPLETE_FILE		3
# define PRINT_FILE			4
# define PRINT_NEXT_FILE	5

typedef struct		s_file
{
	char			*name;
	int				isdir;
	struct s_file	*next;
	struct s_file	*prev;
}					t_file;

typedef struct		s_comp
{
	char			*line;
	char			**buf;
	t_token			*first;
	t_file			*lst;
	int				case_;
	char			*start;
	char			*after;
	int				type;
}					t_comp;

/*
**					ft_completion
*/

int					ft_completion(t_shell *shell, char **buf, int csr);

/*
**					ft_case_opti
*/

int					find_case(t_token *first);
t_file				*opti_ret(char *tmp, t_file *lst);

/*
**					ft_find_file
*/

t_file				*do_it_file(t_comp *comp, char **env);

/*
**					ft_find_cmd
*/

t_file				*do_it_cmd(char *start, char **env);

/*
**					ft_return
*/

int					final_return(t_shell *sh, t_comp *cp, char **ret, int csr);

/*
**					ft_print_lst
*/

void				prepare_ret(t_shell *shell, t_comp *comp, char **tabb);
void				ft_print_one(t_shell *sh, t_comp *comp, char *ret);

/*
**					ft_list_util
*/

char				**lst_to_tab(char **tab, t_file *l);
t_file				*my_lstnew(char *name, int i);
void				my_lst_add(t_file *lst, t_file *add);
t_file				*get_lst_end(t_file *lst, int i);
void				my_free_lst(t_file *lst);

/*
**					ft_util
*/

void				tab_to_str(char **src, char **dst);
char				*find_env(char **env, const char *need);
void				ft_tabdel(char **tab);
int					ft_is_dir(char *pwd);
void				free_token(t_token *list);

#endif
