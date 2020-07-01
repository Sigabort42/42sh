#include "manage_line.h"

static int		banging(t_shell *shell, t_bang *bang)
{
	check_backslash(shell, &shell->tab_history[shell->line_total]);
	while (bang->tmp[bang->i])
	{
		if (bang->tmp[bang->i] == '!' && shell->states[bang->i] == '0' &&
				!ft_isspace(bang->tmp[bang->i++ + 1]))
		{
			if (bang->tmp[bang->i] == '!' && !(bang_previous(shell, bang)))
				return (0);
			else if ((ft_isdigit(bang->tmp[bang->i]) ||
					(bang->tmp[bang->i] == '-' &&
					ft_isdigit(bang->tmp[bang->i + 1]))) &&
					!(bang_n(shell, bang)))
				return (0);
			else if (ft_isprint(bang->tmp[bang->i]) &&
					!(bang_string(shell, bang)))
				return (0);
			continue ;
		}
		bang->line = ft_strjoin_free(bang->line,
				ft_strndup((bang->tmp + bang->i), 1, 0));
		bang->i++;
	}
	return (1);
}

int				manage_bang(t_shell *shell)
{
	int			ret;
	t_bang		bang;

	bang.i = 0;
	bang.tmp = ft_strdup(shell->tab_history[shell->line_total]);
	bang.line = ft_strnew(0);
	shell->bang_modif = 0;
	ret = banging(shell, &bang);
	free(bang.tmp);
	if (ret == 0)
	{
		free(bang.line);
		free(shell->tab_history[shell->line_total]);
		shell->tab_history[shell->line_total] = ft_strdup("");
		return (0);
	}
	ft_strdel(&(shell->tab_history[shell->line_total]));
	shell->tab_history[shell->line_total] = bang.line;
	return (1);
}
