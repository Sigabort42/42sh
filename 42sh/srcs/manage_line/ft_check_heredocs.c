#include "manage_line.h"
#include <term.h>

static char		**get_all_paths(t_shell *shell, char **delimiters)
{
	int		i_path;
	int		nb_delimiters;
	char	**all_paths;

	nb_delimiters = ft_tablen(delimiters);
	if (!(all_paths = (char **)malloc(sizeof(char *) * nb_delimiters + 1)))
		return (NULL);
	i_path = 0;
	while (i_path < nb_delimiters)
	{
		if (!increment_heredoc_tmpfile(shell, &(all_paths[i_path])))
		{
			ft_freetab(all_paths);
			break ;
		}
		i_path++;
	}
	return (all_paths);
}

int				fill_file(t_shell *shell, char *delimiter, int file)
{
	int		ret;
	char	*input;

	while (42)
	{
		ft_putstr("\n> ");
		tputs(tgetstr("sc", 0), 1, ft_putchar);
		input = ft_strnew(0);
		ret = check_end_line(shell, &input, 0);
		if (ret == CTRL_D && ft_strlen(input) == 0)
			break ;
		if (ret == CTRL_C)
		{
			free(input);
			ft_strdel(&shell->tab_history[shell->line_total]);
			return (0);
		}
		if (ft_strequ(input, delimiter))
			break ;
		ft_putstr_fd(input, file);
		ft_putstr_fd("\n", file);
		free(input);
	}
	free(input);
	return (1);
}

int				fill_all_heredocs_files(t_shell *shell, char **all_paths,
char **delimiters)
{
	int		nb_delimiters;
	int		file;
	int		i;

	i = 0;
	nb_delimiters = ft_tablen(delimiters);
	while (i < nb_delimiters)
	{
		if ((file = open(all_paths[i], O_RDWR | O_CREAT, 0644)) == -1)
		{
			ft_putstr("42sh: can't fill the file");
			return (0);
		}
		if (fill_file(shell, delimiters[i], file) == 0)
		{
			close(file);
			delete_n_files(all_paths, i);
			return (0);
		}
		close(file);
		i++;
	}
	return (1);
}

void			change_heredocs_delimiters_by_paths(char **str,
char **delimiters, char **all_paths)
{
	int		i;
	int		i_path;
	int		nb_delimiters;

	i = 0;
	i_path = 0;
	nb_delimiters = ft_tablen(delimiters);
	while (i_path < nb_delimiters && (*str)[i])
	{
		if (ft_strstart(*str + i, "<<") && (i += 2))
		{
			while ((*str)[i] && !ft_strstart(*str + i, delimiters[i_path]))
				i++;
			ft_strcut(str, i, ft_strlen(delimiters[i_path]));
			ft_strpush(str, all_paths[i_path], i);
			i_path++;
		}
		i++;
	}
}

void			check_heredoc(t_shell *shell, char **str)
{
	int		i;
	int		nb_delimiters;
	char	**all_paths;
	char	**delimiters;

	if (!(delimiters = get_delimiters(*str)))
		return ;
	nb_delimiters = ft_tablen(delimiters);
	if ((all_paths = get_all_paths(shell, delimiters)))
	{
		if (fill_all_heredocs_files(shell, all_paths, delimiters))
			change_heredocs_delimiters_by_paths(str, delimiters, all_paths);
		i = 0;
		while (i < nb_delimiters)
			free(all_paths[i++]);
		free(all_paths);
	}
	ft_freetab(delimiters);
}
