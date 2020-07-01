#include "manage_line.h"
#include <term.h>

static void		ft_move_word_moins_before2(t_shell *shell, const char *s,
int *csr)
{
	(*csr)--;
	while (*csr - shell->f_len - 1 >= 0 && s[*csr - shell->f_len] != ' ' &&
			s[*csr - shell->f_len] != '\t')
		(*csr)--;
	while (*csr - shell->f_len - 1 >= 0 && (s[*csr - shell->f_len] == ' ' ||
			s[*csr - shell->f_len] == '\t'))
		(*csr)--;
	while (*csr - shell->f_len - 1 >= 0 && s[*csr - shell->f_len] != ' ' &&
			s[*csr - shell->f_len] != '\t')
		(*csr)--;
	if (*csr - shell->f_len > 0)
		(*csr)++;
}

void			ft_move_word_moins_before(t_shell *shell, const char *s,
int *csr)
{
	int	csr_tmp;

	csr_tmp = *csr;
	if (s[*csr - shell->f_len] == ' ' || s[*csr - shell->f_len] == '\t')
	{
		while (s[*csr - shell->f_len] == ' ' || s[*csr - shell->f_len] == '\t')
			(*csr)--;
		while (s[*csr - shell->f_len] != ' ' && s[*csr - shell->f_len] != '\t')
			(*csr)--;
		(*csr)++;
	}
	else if (*csr - shell->f_len - 1 >= 0)
		ft_move_word_moins_before2(shell, s, csr);
}

void			ft_move_word(t_shell *shell, const char *s, int *csr, int f)
{
	int	csr_tmp;

	csr_tmp = *csr;
	if (f == 1)
	{
		if (s[*csr - shell->f_len] == ' ' || s[*csr - shell->f_len] == '\t')
		{
			while (s[*csr - shell->f_len] == ' ')
				(*csr)++;
		}
		else if (*csr - shell->f_len < (int)ft_strlen(s))
		{
			(*csr)++;
			while (*csr - shell->f_len - 1 >= 0 &&
					ft_isprint(s[*csr - shell->f_len]) &&
						s[*csr - shell->f_len - 1] != ' ')
				(*csr)++;
			while (s[*csr - shell->f_len] == ' ')
				(*csr)++;
		}
	}
	else
		ft_move_word_moins_before(shell, s, csr);
}

void			print_word(char *str)
{
	int		i;

	i = 0;
	while (str[i] && !ft_isalnum(str[i]) && !ft_issign(str[i]))
		i++;
	while (str[i] && !ft_isspace(str[i]))
		ft_putchar(str[i++]);
}

void			ft_freetab(char **to_free)
{
	int		i;

	i = 0;
	while (to_free[i])
	{
		if (to_free[i])
			free(to_free[i]);
		i++;
	}
	free(to_free);
}
