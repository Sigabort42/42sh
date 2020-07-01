#include "manage_line.h"
#include <term.h>

void		suppr_backslash(t_shell *shell, char **line)
{
	int		len;
	int		i;

	i = 0;
	len = ft_strlen(*line);
	while (i < len && (*line)[i])
	{
		if ((*line)[i] == '\'' && shell->states[i] == '0')
		{
			i++;
			while ((*line)[i])
			{
				if ((*line)[i] == '\'' && shell->states[i] == '0')
					break ;
				i++;
			}
		}
		if ((*line)[i] && (*line)[i] == '\\' &&
				(!(*line)[i + 1] || shell->states[i + 1] == '1'))
		{
			ft_strcut(line, i, 1);
			ft_strcut(&shell->states, i, 1);
		}
		i++;
	}
}

void		check_backslash(t_shell *shell, char **line)
{
	int		i;

	i = 0;
	if (shell->states)
		ft_strdel(&(shell->states));
	if (!(shell->states = (char *)malloc(sizeof(char) *
			(ft_strlen(*line) + 1))))
		return ;
	ft_memset(shell->states, '0', ft_strlen(*line));
	while ((*line)[i])
	{
		if ((*line)[i] == '\\' && shell->states[i] == '0')
			shell->states[i++ + 1]++;
		else
			i++;
	}
	shell->states[i] = '\0';
}

static void	get_next_quote(char *str, int *i, char q, char *states)
{
	while (str[*i])
	{
		if (str[*i] == q && states[*i] == '0')
			break ;
		(*i)++;
	}
}

int			ft_next_quote(t_shell *shell, char **str, int *i, char q)
{
	int		ret;

	while (!(*str)[*i])
	{
		*str = ft_strjoin_free(*str, ft_strdup("\n"));
		ft_putstr("\n> ");
		tputs(tgetstr("sc", 0), 1, ft_putchar);
		ret = check_end_line(shell, str, 0);
		if (ret == -1 || ret == CTRL_C || ret == CTRL_D)
		{
			(*str)[ft_strlen(*str) - 1] = '\0';
			if (ret == CTRL_C)
			{
				ft_strdel(str);
				*str = ft_strdup("");
				ft_strdel(&(shell->states));
			}
			return (0);
		}
		check_backslash(shell, str);
		get_next_quote(*str, i, q, shell->states);
	}
	return (1);
}

void		ft_check_quote(t_shell *shell, char **str, char **ev)
{
	int		i;
	char	q;

	i = 0;
	while ((*str)[i])
	{
		if (((*str)[i++] == '\'' || (*str)[i - 1] == '\"') &&
				shell->states[i - 1] == '0')
		{
			q = (*str)[i - 1];
			get_next_quote(*str, &i, q, shell->states);
			if (!ft_next_quote(shell, str, &i, q))
				return ;
			i++;
		}
	}
	change_var_env(shell, str, ev);
}
