#include "builtin.h"

char		**history_append(char **history, char *str)
{
	int		i;
	int		len;
	char	**new;

	len = ft_tablen(history);
	if (!(new = (char **)malloc(sizeof(char *) * (len + 2))))
		return (history);
	i = 0;
	while (history[i])
	{
		new[i] = ft_strdup(history[i]);
		i++;
	}
	new[i] = ft_strdup(str);
	new[i + 1] = NULL;
	ft_freetab(history);
	return (new);
}

void		history_push(t_shell *shell, char *str)
{
	if (ft_strlen(str) <= 0)
		return ;
	shell->line++;
	shell->line_total++;
	if (!shell->tab_session)
		shell->tab_session = (char **)ft_memalloc(sizeof(char *) * 2);
	if (!shell->tab_history)
		shell->tab_history = (char **)ft_memalloc(sizeof(char *) * 2);
	shell->tab_session = history_append(shell->tab_session, str);
	shell->tab_history = history_append(shell->tab_history, str);
}

char		**ft_filetotab(char *path)
{
	int		fd;
	char	*buff;
	char	*line;
	char	**file_tab;

	if ((fd = open(path, O_RDONLY)) == -1)
		return (NULL);
	line = ft_strnew(0);
	buff = ft_strnew(4097);
	while (read(fd, buff, 4096) > 0)
		line = ft_strjoin_free(line, buff);
	file_tab = ft_strsplit(line, '\n');
	free(line);
	close(fd);
	return (file_tab);
}

static int	ft_make_options(char *option, char set[])
{
	int i;
	int i2;
	int options;

	if (option && *option && *option != '-')
	{
		ft_putstr("42sh: history: ");
		ft_putstr(option);
		ft_putstr(": numeric argument required\n");
		return (-1);
	}
	if (!option)
		return (0);
	i = 1;
	options = 0;
	while (option[i])
	{
		i2 = 0;
		while (set[i2] && set[i2] != option[i])
			i2++;
		if (set[i2])
			options |= ft_recursive_power(2, i2);
		i++;
	}
	return (options);
}

int			ft_builtin_history(t_shell *shell, t_process *prog)
{
	int		options;

	if (!ft_history_usage(prog->args[1]))
		return (0);
	if ((options = ft_make_options(prog->args[1], HIST_OP)) == -1)
		return (0);
	if (!options)
		history_print(shell);
	if (IS_OP(options, HIST_OP_CLEAR))
		history_clear(shell);
	if (IS_OP(options, HIST_OP_DELOFFSET) && prog->args[2])
		history_delete_offset(shell, ft_atoi(prog->args[2]));
	if (IS_OP(options, HIST_OP_SESSTOFILE))
		session_to_file(shell, prog->args[2]);
	if (IS_OP(options, HIST_OP_ADDFILE))
		history_add_file(shell, prog->args[2]);
	if (IS_OP(options, HIST_OP_ADDUNREAD))
		history_add_unread(shell, prog->args[2]);
	if (IS_OP(options, HIST_OP_WRITE))
		history_write(shell, prog->args[2]);
	if (IS_OP(options, HIST_OP_SUBSITUTE) && prog->args[2])
		history_subsitution((prog->args + 2));
	if (IS_OP(options, HIST_OP_ADD) && prog->args[2])
		history_add(shell, (prog->args + 2));
	return (0);
}
