#include "manage_line.h"
#include <term.h>

int				check_ret(t_shell *shell, int ret, int *csr)
{
	if (ret == CTRL_C || ret == CTRL_D)
	{
		if (ret == CTRL_C)
		{
			free(shell->tab_history[shell->line_total]);
			shell->tab_history[shell->line_total] = ft_strdup("");
			return (1);
		}
		else if (ret == CTRL_D &&
				ft_strlen(shell->tab_history[shell->line]) < 1)
		{
			ft_putstr("exit");
			free(shell->tab_history[shell->line_total]);
			shell->tab_history[shell->line_total] = ft_strdup("exit");
			return (1);
		}
		else if (ret == CTRL_D && *csr >= shell->f_len && *csr - shell->f_len <
				(int)ft_strlen(shell->tab_history[shell->line]))
			ft_strcut(&(shell->tab_history[shell->line]),
					*csr - shell->f_len, 1);
		return (0);
	}
	return (0);
}

int				ft_complete_line2(t_shell *shell, int *ret)
{
	if (*ret > 0 && *ret != 3)
	{
		if ((*ret = line_end(shell, shell->tab_history[shell->line_total])))
		{
			ft_putstr("\n> ");
			tputs(tgetstr("sc", 0), 1, ft_putchar);
			if ((*ret = check_end_line(shell,
					&shell->tab_history[shell->line_total], *ret)) == -1)
				return (-1);
			if (*ret == CTRL_C)
			{
				free(shell->tab_history[shell->line_total]);
				shell->tab_history[shell->line_total] = ft_strdup("");
			}
			if (*ret == CTRL_D)
				return (-1);
		}
	}
	return (*ret);
}

int				ft_complete_line(t_shell *shell)
{
	int		ret;

	ret = 1;
	while (ret > 0)
	{
		check_backslash(shell, &shell->tab_history[shell->line_total]);
		ft_check_quote(shell,
				&(shell->tab_history[shell->line_total]), shell->init.evp);
		if ((ret = line_end(shell, shell->tab_history[shell->line_total])) == 3)
		{
			ft_putstr("\n> ");
			tputs(tgetstr("sc", 0), 1, ft_putchar);
			ret = check_end_line(shell,
					&shell->tab_history[shell->line_total], ret);
			if (ret == -1 || ret == CTRL_D)
				return (0);
			if (ret == CTRL_C)
			{
				free(shell->tab_history[shell->line_total]);
				shell->tab_history[shell->line_total] = ft_strdup("");
			}
		}
		ret = ft_complete_line2(shell, &ret);
	}
	return (1);
}

void			change_tield_by_home(t_shell *shell, char **line)
{
	char	*path_home;
	int		i;

	i = 0;
	path_home = ft_strchr(shell->init.evp[ft_search_var_env(shell->init.evp,
			"HOME")], '=') + 1;
	while ((*line)[i])
	{
		if (ft_strnequ(*line + i, "~", 1) && !ft_isalnum((*line)[i + 1]))
		{
			ft_strcut(line, i, 1);
			ft_strpush(line, path_home, i);
			while ((*line)[i] && !ft_isspace((*line)[i]))
				i++;
		}
		else if (ft_strnequ(*line + i, "~/", 2))
		{
			ft_strcut(line, i, 2);
			ft_strpush(line, path_home, i);
			while ((*line)[i] && !ft_isspace((*line)[i]))
				i++;
		}
		else
			i++;
	}
}

void			ft_check_line(t_shell *shell)
{
	if (shell->line != shell->line_total)
		refresh_line(shell);
	if (ft_strstr(shell->tab_history[shell->line_total], "!") &&
			manage_bang(shell) && shell->bang_modif)
	{
		ft_putchar('\n');
		ft_putstr(shell->tab_history[shell->line_total]);
	}
	ft_complete_line(shell);
	check_backslash(shell, &shell->tab_history[shell->line_total]);
	suppr_backslash(shell, &shell->tab_history[shell->line_total]);
	ft_strdel(&(shell->states));
	if (!ft_strlen(shell->tab_history[shell->line_total]))
		return ;
	history_push(shell, shell->tab_history[shell->line_total]);
	check_inhib_operators(shell, &shell->tab_history[shell->line_total]);
	free(shell->states);
	if (shell->tab_history[shell->line_total] &&
			ft_strstr(shell->tab_history[shell->line_total], "<<"))
		check_heredoc(shell, &shell->tab_history[shell->line_total]);
	if (shell->tab_history[shell->line_total] &&
			ft_strchr(shell->tab_history[shell->line_total], '~'))
		change_tield_by_home(shell, &shell->tab_history[shell->line_total]);
}
