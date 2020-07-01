#include "manage_line.h"

int				bang_previous(t_shell *shell, t_bang *bang)
{
	if (!shell->line_total)
	{
		ft_putstr("\n42_SuperSayen: !!: event not found");
		return (0);
	}
	bang->line = ft_strjoin_free(bang->line,
			ft_strdup(shell->tab_history[shell->line_total - 1]));
	bang->i++;
	shell->bang_modif = 1;
	return (1);
}

static void		print_bang_n_errors(char *tmp, int nbr)
{
	if (!nbr)
	{
		ft_putchar('\n');
		ft_putstr("42sh: !");
		ft_putnbr(nbr);
		ft_putstr(": event not found");
		return ;
	}
	ft_putchar('\n');
	ft_putstr("42sh !");
	ft_putstr(tmp);
	ft_putnbr(nbr);
	ft_putstr(": event not found");
}

int				bang_n(t_shell *shell, t_bang *bang)
{
	char	*tmp;
	int		nbr;

	tmp = "";
	nbr = ft_atoi(&bang->tmp[bang->i]);
	if (!nbr || (nbr < 0 && nbr < -shell->line_total))
	{
		if (bang->tmp[bang->i] == '-' && !nbr)
			tmp = "-";
		print_bang_n_errors(tmp, nbr);
		return (0);
	}
	if (nbr < 0)
		nbr = nbr * -1;
	if (nbr >= shell->line_total)
	{
		print_bang_n_errors(NULL, nbr);
		return (0);
	}
	bang->line = ft_strjoin_free(bang->line,
			ft_strdup(shell->tab_history[nbr - 1]));
	while (bang->tmp[bang->i] && ft_isdigit(bang->tmp[bang->i]))
		bang->i++;
	shell->bang_modif = 1;
	return (1);
}

int				bang_string(t_shell *shell, t_bang *bang)
{
	int		i;
	char	*word;

	i = shell->line_total;
	word = get_name(&(bang->tmp[bang->i]));
	while (i > 0 && shell->tab_history[i])
	{
		if (ft_strstart(shell->tab_history[i], word))
			break ;
		i--;
	}
	if (!shell->tab_history[i])
	{
		ft_strdel(&word);
		return (0);
	}
	bang->line = ft_strjoin_free(bang->line,
			ft_strdup(shell->tab_history[i]));
	bang->i += ft_strlen(word);
	shell->bang_modif = 1;
	ft_strdel(&word);
	return (1);
}
