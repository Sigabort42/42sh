#include "manage_line.h"

int				increment_heredoc_tmpfile(t_shell *shell, char **path)
{
	int		file;

	*path = ft_strjoin_free(ft_strdup("/tmp/42sh_tmp_heredoc_"),
			ft_itoa(shell->heredoc++));
	while ((*path) && access(*path, F_OK) == 0)
	{
		ft_strdel(path);
		if (shell->heredoc < INT_MAX)
		{
			*path = ft_strdup("/tmp/42sh_tmp_heredoc_");
			*path = ft_strjoin_free(*path, ft_itoa(shell->heredoc++));
		}
		else
			return (0);
	}
	if (access(*path, W_OK) == 0)
	{
		ft_strdel(path);
		return (0);
	}
	if ((file = open(*path, O_RDWR | O_CREAT, 0644)) == -1)
		return (0);
	close(file);
	return (1);
}

void			delete_n_files(char **all_paths, int n)
{
	int		i;

	i = 0;
	while (i < n && all_paths[i])
	{
		if (access(all_paths[i], F_OK) == 0)
			unlink(all_paths[i]);
		i++;
	}
}

static char		*get_delim_heredoc(char *str, char c)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (ft_strchr("&| \t", str[i]) || (c && str[i] == c))
			break ;
		i++;
	}
	if (i == 0)
		return (NULL);
	return (ft_strndup(str, i, 0));
}

int				check_delim_heredoc(char **str, int *i, char **delim,
char **delims)
{
	char	c;

	c = 0;
	while ((*str)[*i] && ft_isspace((*str)[*i]))
		(*i)++;
	if ((*str)[*i] && ((*str)[*i] == '"' || (*str)[*i] == '\''))
	{
		c = (*str)[*i];
		(*str)[*i] = ' ';
		(*i)++;
	}
	if ((*str)[*i] && (*delim = get_delim_heredoc((*str) + *i, c)))
		*i += ft_strlen(*delim) - 1;
	else
		return (0);
	if (c)
		(*str)[*i + 1] = ' ';
	*delims = ft_strjoin_free(*delims, *delim);
	*delims = ft_strjoin_free(*delims, ft_strdup("|"));
	return (1);
}

char			**get_delimiters(char *str)
{
	int		i;
	char	*delim;
	char	*all_delimiters;
	char	**tab_delimiters;

	i = 0;
	delim = NULL;
	all_delimiters = ft_strnew(0);
	while (str[i])
	{
		if (ft_strnequ("<<", str + i, 2) && (i += 2))
		{
			if (!check_delim_heredoc(&str, &i, &delim, &all_delimiters))
			{
				free(all_delimiters);
				return (NULL);
			}
		}
		i++;
	}
	tab_delimiters = ft_strsplit_charset(all_delimiters, "|");
	free(all_delimiters);
	if (!tab_delimiters)
		return (NULL);
	return (tab_delimiters);
}
