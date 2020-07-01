#include "manage_line.h"
#include <term.h>

static void		ft_history(t_shell *shell, int line, int *csr)
{
	if (line >= 0 && line <= shell->line_total)
		*csr = ft_strlen(shell->tab_history[shell->line]) + shell->f_len;
	else if (line >= shell->line_total)
		shell->line = shell->line_total - 1;
	else
		shell->line = 0;
}

static int		ft_moveone_cut_and_delete2(char **buf, char *c, int *csr,
t_shell *shell)
{
	if (c[0] == 27 && c[2] == 68)
		if (*csr > shell->f_len)
			(*csr)--;
	if (c[0] == 27 && c[2] == 67)
		if (*csr < (int)ft_strlen(*buf) + shell->f_len)
			(*csr)++;
	if (c[0] == 11)
	{
		shell->buf_mem = ft_strdup(&(*(buf))[*csr - shell->f_len]);
		*buf = ft_strndup(*buf, *csr - shell->f_len, 1);
	}
	return (1);
}

int				ft_moveone_cut_and_delete(char **buf, char *c, int *csr,
t_shell *shell)
{
	char	*tmp;

	if (!ft_moveone_cut_and_delete2(buf, c, csr, shell))
		;
	else if (c[0] == 127 && *csr > shell->f_len)
	{
		ft_strcpy(*buf + *csr - shell->f_len - 1, *buf + *csr - shell->f_len);
		(*csr)--;
	}
	else if (c[0] == 27 && c[2] == 49 && c[5] == 67)
	{
		tmp = ft_strndup(*buf, (*csr) - shell->f_len, 0);
		ft_putstr_fd(tmp, shell->fd_tty);
		free(tmp);
		tmp = ft_strndup(*buf, (*csr) + 1 - shell->f_len, 0);
		ft_putstr_fd(tmp, shell->fd_tty);
		(*csr)++;
	}
	else
		return (0);
	return (1);
}

void			ft_moveword_home_end_history(char **buf, char *c, int *csr,
t_shell *shell)
{
	if (c[0] == 2)
		ft_move_word(shell, *buf, csr, 0);
	else if (c[0] == 6)
		ft_move_word(shell, *buf, csr, 1);
	else if (c[0] == 1 && *csr > shell->f_len)
		*csr = shell->f_len;
	else if (c[0] == 5 && *csr < (int)ft_strlen(*buf))
		*csr = (int)ft_strlen(*buf) + shell->f_len;
	else if (c[0] == 27 && (c[2] == 65))
		ft_history(shell, --shell->line, csr);
	else if (c[0] == 27 && c[2] == 66 && shell->line < shell->line_total)
		ft_history(shell, ++shell->line, csr);
}

void			ft_move_line_up_down(char *c, int *csr, t_shell *shell)
{
	if (c[5] == 65 && *csr - shell->tc.wsize.ws_col >= shell->f_len)
		*csr -= shell->tc.wsize.ws_col;
	if (c[5] == 66 && *csr + shell->tc.wsize.ws_col - shell->f_len - 1 <
			(int)ft_strlen(shell->tab_history[shell->line]))
		*csr += shell->tc.wsize.ws_col;
}
