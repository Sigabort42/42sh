#include "completion.h"
#include <term.h>

static void	back_to_line(void)
{
	char	*cr;
	char	*od;

	cr = tgetstr("cr", 0);
	od = tgetstr("do", 0);
	if (!cr || !od)
		back_to_line();
	else
	{
		tputs(cr, 1, ft_putchar);
		tputs(od, 1, ft_putchar);
	}
}

static void	print_ret(char **tabb, size_t max, int word_per_l)
{
	int		i;
	size_t	len;

	i = 0;
	while (tabb[i])
	{
		len = ft_strlen(tabb[i]);
		ft_putstr(tabb[i]);
		if (i > 0 && word_per_l > 0 && (i + 1) % word_per_l == 0)
		{
			if (tabb[i + 1])
				back_to_line();
		}
		else
		{
			while (len++ <= max)
				ft_putchar(' ');
		}
		i++;
	}
}

static void	put_another_line(t_shell *shell)
{
	ft_putstr(shell->format);
	ft_putstr(shell->tab_history[shell->line]);
	back_to_line();
	ft_putstr("> ");
}

void		prepare_ret(t_shell *shell, t_comp *comp, char **tabb)
{
	int		i;
	size_t	max;
	int		word_per_l;

	i = -1;
	max = 2;
	if (!tabb)
		return ;
	while (tabb[++i])
		if (ft_strlen(tabb[i]) > max)
			max = ft_strlen(tabb[i]);
	if (max <= 1)
		return ;
	ioctl(shell->fd_tty, TIOCGWINSZ, &shell->tc.wsize);
	word_per_l = shell->tc.wsize.ws_col / ((int)max + 1);
	back_to_line();
	print_ret(tabb, max, word_per_l);
	back_to_line();
	if (comp->type)
		put_another_line(shell);
	ft_putstr(shell->format);
}
