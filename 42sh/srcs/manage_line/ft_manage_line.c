#include "completion.h"
#include "manage_line.h"
#include "env.h"
#include <term.h>

static void		ft_copy_buf(char *buf, int *csr, char *c, t_shell *shell)
{
	static int	flag = 0;

	if (c[0] == 7 && !flag && (flag = 1))
	{
		shell->csr_copy = *csr - shell->f_len;
		return ;
	}
	if (shell->csr_copy < *csr - shell->f_len)
		shell->buf_mem = ft_strsub(buf, shell->csr_copy, *csr - shell->f_len);
	else
		shell->buf_mem = ft_strsub(buf, *csr - shell->f_len, shell->csr_copy);
	flag = 0;
}

static void		ft_tch_colle_buf(char **buf, int *csr, t_shell *shell)
{
	char	*tmp;

	ft_putstr_fd(shell->buf_mem, shell->fd_tty);
	if (*csr < (int)ft_strlen(*buf) + shell->f_len)
	{
		tmp = ft_strdup(&(*(buf))[*csr - shell->f_len]);
		ft_bzero(&(*(buf))[*csr - shell->f_len], 1);
		*csr = (int)ft_strlen(*buf) +
			(int)ft_strlen(shell->buf_mem) + shell->f_len;
		tmp = ft_strjoin_free(shell->buf_mem, tmp);
		*buf = ft_strjoin_free(*buf, tmp);
	}
	else
	{
		*buf = ft_strjoin_free(*buf, shell->buf_mem);
		*csr = (int)ft_strlen(*buf) + shell->f_len;
	}
	shell->buf_mem = 0;
}

void			ft_verif_c2(t_shell *shell, char *c, int *csr, char **buf)
{
	if (ft_moveone_cut_and_delete(buf, c, csr, shell))
		;
	else if (c[0] == 21 && shell->buf_mem)
		ft_tch_colle_buf(buf, csr, shell);
	else if (c[0] == 27 && c[2] == 49 && c[3] == 59 &&
			(c[5] == 66 || c[5] == 65))
		ft_move_line_up_down(c, csr, shell);
	else
		ft_moveword_home_end_history(buf, c, csr, shell);
}

int				ft_verif_c(t_shell *shell, char *c, int *csr, char **buf)
{
	char	*tmp;

	if (c[0] == 3 || c[0] == 4)
		return (c[0] == 3 ? CTRL_C : CTRL_D);
	if (c[0] == 7)
		ft_copy_buf(*buf, csr, c, shell);
	else if (c[0] == 9)
		(*csr) = ft_completion(shell, buf, *csr);
	else if (c[0] >= 32 && c[0] <= 126)
	{
		if ((*buf && *csr < (int)ft_strlen(*buf) + shell->f_len))
		{
			tmp = ft_strdup(&(*(buf))[*csr - shell->f_len]);
			ft_bzero(&(*(buf))[*csr - shell->f_len], 3);
			tmp = ft_strjoin_free(ft_strdup(c), tmp);
			*buf = ft_strjoin_free(*buf, tmp);
		}
		else
			*buf = ft_strjoin_free(*buf, ft_strdup(c));
		(*csr)++;
	}
	else
		ft_verif_c2(shell, c, csr, buf);
	return (1);
}

char			*ft_manage_line(t_shell *shell)
{
	char	*c;
	int		csr;
	int		ret;

	ret = 0;
	c = ft_strnew(6);
	c[0] = 1;
	ft_init_manage(shell);
	csr = shell->f_len;
	tputs(tgetstr("sc", 0), 1, ft_putchar);
	while (ret != 4 && (ret = read(0, c, 6)) > 0 && c[0] != 10)
	{
		c[ret] = '\0';
		ret = ft_verif_c(shell, c, &csr, &(shell->tab_history[shell->line]));
		if (check_ret(shell, ret, &csr))
			break ;
		ft_refresh_line(shell, shell->tab_history[shell->line], csr);
	}
	free(c);
	if (ret != CTRL_C)
		ft_check_line(shell);
	free(shell->format);
	return (shell->tab_history[shell->line_total]);
}
