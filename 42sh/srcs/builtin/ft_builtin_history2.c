#include "builtin.h"

void		history_write_session(t_shell *shell)
{
	int		i;
	int		fd;

	if ((fd = open(shell->chemin_history,
			O_RDWR | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) == -1)
		return ;
	lseek(fd, 0, SEEK_END);
	i = 0;
	while (shell->tab_session[i + 1])
		ft_putendl_fd(shell->tab_session[i++], fd);
	close(fd);
}

void		history_write(t_shell *shell, char *file)
{
	int		i;
	int		fd;

	if (file)
	{
		if ((fd = open(file, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR)) == -1)
			return ;
	}
	else if ((fd = open(shell->chemin_history,
			O_RDWR | O_TRUNC | O_CREAT, S_IRUSR |
			S_IWUSR | S_IRGRP | S_IROTH)) == -1)
		return ;
	i = 0;
	while (shell->tab_history[i + 1])
		ft_putendl_fd(shell->tab_history[i++], fd);
	close(fd);
}

void		history_add_unread(t_shell *shell, char *file)
{
	char	c;
	int		fd;

	if (file && (fd = open(file,
			O_RDWR | O_TRUNC | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP |
			S_IROTH)) == -1)
		return ;
	else if ((fd = open(shell->chemin_history,
			O_RDWR | O_TRUNC | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP |
			S_IROTH)) == -1)
		return ;
	while (read(fd, &c, 1) > 0)
		;
	while (shell->tab_session[shell->line_session])
		ft_putendl_fd(shell->tab_session[shell->line_session++], fd);
	close(fd);
}

void		history_subsitution(char **args)
{
	int		i;

	i = 0;
	while (args[i])
		ft_putendl(args[i++]);
}

void		history_add(t_shell *shell, char **args)
{
	int		fd;
	char	*line;

	if (!(line = ft_concat_tab(args, " ")))
		return ;
	if ((fd = open(shell->chemin_history,
			O_RDWR | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) == -1)
		return ;
	lseek(fd, 0, SEEK_END);
	ft_putendl_fd(line, fd);
	free(line);
	close(fd);
}
