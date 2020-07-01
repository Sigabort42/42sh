#ifndef ENV_H
# define ENV_H

# include "manage_line.h"
# include <sys/stat.h>

typedef struct stat	t_stat;

typedef struct		s_env
{
	char			*name;
	char			*value;
	t_shell			*shell;
	struct s_env	*prev;
	struct s_env	*next;
}					t_env;

t_env				*g_env;

/*
**		utils for environment
*/
int					env_get_size(t_env *list);
t_env				*env_create_elem(const char *name, const char *value);
void				env_push_back(t_env **list, t_env *elem);
int					ft_init_env_from_tab(char **env);
char				**ft_copy_env_to_tab(t_env *list);
char				**ft_copy_path(t_env *list);
t_env				*ft_duplicate_env(t_env *list);
void				flush_env(t_env **list);
/*
**		manage environment
*/
void				ft_print_env(t_env *list);
int					ft_default_env(void);
t_env				*ft_getenv(t_env *list, const char *name);
int					ft_unsetenv(t_env **list, const char *name);
int					ft_setenv(t_env **list, const char *name,
						const char *value, int overwrite);

#endif
