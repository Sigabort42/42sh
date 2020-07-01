#include "builtin.h"

int		ft_history_usage(char *list)
{
	int		i;

	if (!list)
		return (1);
	if (list[0] != '-' || (list[0] == '-' && !list[1]))
	{
		ft_putstr("42sh: history: ");
		ft_putstr(list);
		ft_putstr(": numeric argument required\n");
		return (0);
	}
	i = 1;
	while (list[i] && ft_strchr(HIST_OP, list[i]))
		i++;
	if (!list[i])
		return (1);
	ft_putstr("42sh: history: -");
	ft_putchar(list[i]);
	ft_putstr(": invalid option");
	ft_putstr("history: usage: history [-c] [-d offset] [n] or history");
	ft_putstr("-awrn [filename] or history -ps arg [arg...]\n");
	return (0);
}
