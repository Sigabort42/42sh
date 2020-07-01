#include "manage_line.h"
#include <term.h>

static int	fill_end_line(t_shell *shell, char **buf)
{
	int		ret;
	int		csr;
	char	*c;

	csr = 2;
	c = ft_strnew(6);
	while ((ret = read(0, c, 6)) > 0 && c[0] != 10)
	{
		c[ret] = '\0';
		ret = ft_verif_c(shell, c, &csr, buf);
		if (ret == CTRL_D && ft_strlen(*buf) > 0)
			ft_strcut(buf, csr - shell->f_len, 1);
		else if (ret == CTRL_C || ret == CTRL_D)
		{
			free(c);
			return (ret);
		}
		ft_refresh_line(shell, *buf, csr);
	}
	free(c);
	return (ret);
}

int			check_end_line(t_shell *shell, char **to_append, int s)
{
	int		ret;
	int		save;
	char	*buf;

	save = shell->f_len;
	shell->f_len = 2;
	shell->isline = 0;
	buf = ft_strnew(0);
	ret = fill_end_line(shell, &buf);
	if (ret == CTRL_C || (ret == CTRL_D && !ft_strlen(buf)))
	{
		shell->isline = 1;
		ft_strdel(&buf);
		return (ret);
	}
	*to_append = ft_strjoin_free(*to_append, buf);
	shell->f_len = save;
	shell->isline = 1;
	return (s);
}

void		check_inhib_operators(t_shell *shell, char **str)
{
	int		x;
	int		i;

	if (!shell->states)
		return ;
	i = 0;
	while ((*str)[i])
	{
		x = 0;
		while (shell->operators[x])
		{
			if (*(shell->operators[x]) == (*str)[i] && shell->states[i] == '1')
			{
				ft_strpush(str, "'", i + 1);
				ft_strpush(str, "'", i);
			}
			x++;
		}
		i++;
	}
}

void		refresh_line(t_shell *shell)
{
	free(shell->tab_history[shell->line_total]);
	shell->tab_history[shell->line_total] =
			ft_strdup(shell->tab_history[shell->line]);
}

char		*get_name(char *str)
{
	int		i;

	i = 0;
	while (str[i] && ft_isalnum(str[i]))
		i++;
	if (i <= 0)
		i++;
	return (ft_strndup(str, i, 0));
}
