#include "manage_line.h"
#include <term.h>
#include "env.h"

void		get_prompt(t_shell *shell, char **prompt)
{
	t_env	*env_tmp;

	(void)shell;
	if ((env_tmp = ft_getenv(g_env, "PWD")))
	{
		*prompt = ft_strjoin("\033[32m[", ft_strrchr(env_tmp->value, '/') + 1);
		*prompt = ft_strjoin_free(*prompt, ft_strdup("]\033[0m"));
	}
	else
		*prompt = ft_strdup("\033[36m[21sh]\033[0m");
}

void		ft_init_manage(t_shell *shell)
{
	int		i;

	if (!isatty(1))
		exit(1);
	i = 0;
	shell->fd_tty = 1;
	shell->quote = 0;
	shell->heredoc = 0;
	shell->isline = 1;
	shell->states = NULL;
	get_prompt(shell, &(shell->format));
	shell->f_len = ft_strlen(shell->format) - 8;
	ft_putstr(shell->format);
	tputs(tgetstr("cr", 0), 1, ft_putchar);
	while (i++ < shell->f_len)
		tputs(tgetstr("nd", 0), 1, ft_putchar);
	tputs(tgetstr("cd", 0), 1, ft_putchar);
	while (shell->tab_history[shell->line + 1])
		shell->line++;
	if (shell->line > shell->line_total)
		shell->line_total = shell->line;
	shell->tab_history[shell->line] = ft_strdup("");
}

int			ft_search_var_env(char **evp, char *varia)
{
	int		i;

	i = 0;
	while (evp[i])
	{
		if (!ft_strncmp(evp[i], varia, ft_strlen(varia)))
			return (i);
		i++;
	}
	return (-1);
}

char		**ft_copy_evp(char **evp)
{
	int		i;
	char	**ev;

	i = 0;
	while (evp[i])
		i++;
	if ((ev = (char **)malloc(sizeof(char*) * (i + 1))) == 0)
	{
		ft_putendl_fd("no space memory", 2);
		exit(1);
	}
	i = 0;
	while (evp[i])
	{
		ev[i] = ft_strdup(evp[i]);
		i++;
	}
	ev[i] = 0;
	return (ev);
}

char		**ft_str2join_free(char **tab1, char **tab2, int free)
{
	char	**join;
	int		i;
	int		i2;

	i = ft_tablen(tab1) + ft_tablen(tab2);
	if (!(join = (char **)malloc(sizeof(char *) * (i + 1))))
		return (NULL);
	i = 0;
	i2 = 0;
	while (tab1[i])
		join[i2++] = ft_strdup(tab1[i++]);
	i = 0;
	while (tab2[i])
	{
		join[i2 + i] = ft_strdup(tab2[i]);
		i++;
	}
	join[i2 + i] = NULL;
	if (free == 1 || free == 3)
		ft_freetab(tab1);
	if (free >= 2)
		ft_freetab(tab2);
	return (join);
}
