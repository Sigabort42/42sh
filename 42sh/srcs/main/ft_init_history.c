#include "ft_signal.h"
#include "jobs.h"
#include "lexer.h"
#include "tree.h"
#include "env.h"
#include "exec.h"
#include "manage_line.h"
#include <term.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <curses.h>

int			ft_count_line(char *chemin)
{
	int		i;
	int		fd;
	char	c[1];

	i = 0;
	if ((fd = open(chemin, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR |
					S_IRGRP | S_IROTH)) == -1)
		return (-1);
	if (fd != -1)
	{
		while (read(fd, c, 1) > 0)
			if (*c == '\n')
				i++;
	}
	close(fd);
	return (i);
}

void		ft_strappend(char **str, char c)
{
	int		len;
	char	*new;

	len = ft_strlen(*str);
	if (!(new = (char *)malloc(sizeof(char) * (len + 2))))
		return ;
	ft_strcpy(new, *str);
	new[len] = c;
	free(*str);
	*str = new;
}

static void	get_history(t_shell *shell, char **history, int fd, int len)
{
	int		i;
	int		i2;
	char	*d;
	char	*to_split;

	i = 0;
	i2 = 0;
	d = ft_strnew(1);
	shell->octet_hist = 0;
	to_split = ft_strnew(0);
	while (read(fd, d, 1) > 0)
	{
		to_split = ft_strjoin_free(to_split, ft_strdup(d));
		shell->octet_hist++;
	}
	free(d);
	while (i < len)
	{
		history[i++] = ft_strcdup(to_split + i2, '\n');
		while (to_split[i2] && to_split[i2] != '\n')
			i2++;
		i2++;
	}
	free(to_split);
}

static void	ft_init_history2(t_shell *shell)
{
	if ((shell->line = ft_count_line(shell->chemin_history)) == -1)
	{
		ft_putstr_fd("no history possible", shell->fd_tty);
		exit(-1);
	}
	shell->line_total = shell->line;
	if (shell->line < 0 || !(shell->tab_history =
				(char **)malloc(sizeof(char *) * (shell->line + 2))))
	{
		if (shell->line > 0)
			ft_putstr_fd("no place memory", shell->fd_tty);
		exit(1);
	}
	if (shell->fd_history != -1)
	{
		get_history(shell, shell->tab_history, shell->fd_history, shell->line);
		close(shell->fd_history);
	}
	shell->tab_history[shell->line_total + 1] = NULL;
}

void		ft_init_history(t_shell *shell)
{
	int		i;

	i = 0;
	shell->chemin_history =
		ft_strjoin(&shell->init.evp[ft_search_var_env(shell->init.evp,
					"HOME")][5], "/.42sh_history");
	if ((shell->fd_history = open(shell->chemin_history, O_RDWR | O_CREAT,
					S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) != -1)
		ft_init_history2(shell);
	else
		ft_putstr_fd("no history possible", shell->fd_tty);
	shell->line_session = 0;
	close(shell->fd_history);
}
