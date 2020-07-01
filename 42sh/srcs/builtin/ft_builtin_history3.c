#include "builtin.h"

void		history_delete_offset(t_shell *shell, int offset)
{
	char	*swap;
	int		i;

	if (offset >= shell->line_total || offset <= 0)
		return ;
	i = 0;
	while ((i + 1) < offset)
		i++;
	while (shell->tab_history[i] && shell->tab_history[i + 1])
	{
		swap = shell->tab_history[i];
		shell->tab_history[i] = shell->tab_history[i + 1];
		shell->tab_history[i + 1] = swap;
		i++;
	}
	free(shell->tab_history[i + 1]);
	shell->tab_history[i] = NULL;
	shell->line_total--;
	shell->line--;
}

void		history_clear(t_shell *shell)
{
	int		file;
	int		i;

	if ((file = open(shell->chemin_history, O_RDWR | O_TRUNC | O_CREAT,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) != -1)
		close(file);
	i = 0;
	while (i < shell->line_total)
	{
		free(shell->tab_history[i]);
		i++;
	}
	free(shell->tab_history);
	shell->tab_history = (char **)ft_memalloc(sizeof(char *) * 2);
	shell->line = 0;
	shell->line_total = 0;
}

void		session_to_file(t_shell *shell, char *file)
{
	int		i;
	int		fd;

	if (file)
	{
		if ((fd = open(file, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR)) == -1)
			return ;
	}
	else
	{
		if ((fd = open(shell->chemin_history, O_RDWR | O_CREAT,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) == -1)
			return ;
		lseek(fd, 0, SEEK_END);
	}
	i = 0;
	while (shell->tab_session[i])
		ft_putendl_fd(shell->tab_session[i++], fd);
	close(fd);
}

void		history_add_file(t_shell *shell, char *file)
{
	char	**tmp;

	if (file)
		tmp = ft_filetotab(file);
	else
		tmp = ft_filetotab(shell->chemin_history);
	shell->tab_history = ft_str2join_free(shell->tab_history, tmp, 2);
	while (shell->tab_history[shell->line + 1])
		shell->line++;
	shell->line_total = shell->line;
	shell->tab_history[shell->line - 1] =
			shell->tab_history[shell->line];
	shell->tab_history[shell->line] = NULL;
}

void		history_print(t_shell *shell)
{
	int		tmp;
	int		i;

	i = 0;
	while (shell->tab_history[i] && i < shell->line_total)
	{
		tmp = ft_intlen(shell->line_total) - ft_intlen(i + 1) + 1;
		while (tmp--)
			ft_putchar(' ');
		ft_putnbr(i + 1);
		ft_putstr("  ");
		ft_putstr(shell->tab_history[i]);
		ft_putchar('\n');
		i++;
	}
}
