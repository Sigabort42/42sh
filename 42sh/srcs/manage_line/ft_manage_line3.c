#include "manage_line.h"
#include <term.h>

void			ft_refresh_line(t_shell *shell, char *line, int csr)
{
	int		i;
	int		x;

	i = 0;
	x = 4;
	if (shell->f_len == 2)
		x -= 3;
	ioctl(shell->fd_tty, TIOCGWINSZ, &shell->tc.wsize);
	tputs(tgetstr("rc", 0), 1, ft_putchar);
	tputs(tgetstr("cd", 0), 1, ft_putchar);
	if (line)
		ft_putstr_fd(line, 0);
	tputs(tgetstr("rc", 0), 1, ft_putchar);
	while (i < csr - shell->f_len && line[i])
	{
		if (line[i] == '\n' ||
				!((i + shell->f_len + x) % shell->tc.wsize.ws_col))
		{
			tputs(tgetstr("cr", 0), 1, ft_putchar);
			tputs(tgetstr("do", 0), 1, ft_putchar);
		}
		else
			tputs(tgetstr("nd", 0), 1, ft_putchar);
		i++;
	}
}

int				line_end(t_shell *shell, char *str)
{
	int		i;
	int		s;
	int		x;

	if (!str)
		return (0);
	s = 0;
	i = ft_strlen(str) - 1;
	while (i >= 0 && ft_isspace(str[i]))
		i--;
	while (shell->operators[s])
	{
		x = 0;
		while (i - x >= 0 && shell->operators[s][x] ==
				str[i - x] && shell->states[i] == '0')
			x++;
		if (x == 2 || (x == 1 && ft_strlen(shell->operators[s]) == 1))
		{
			if (s == 3 && shell->states[i] == '1')
				return (0);
			return (s + 1);
		}
		s++;
	}
	return (0);
}
