#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include "libft.h"

int	read_stdin(char **line)
{
	int		ret;
	char	buff[256 + 1];
	char	*tmp;

	(*line) = ft_strnew(0);
	ft_memset(buff, 0, 256 + 1);
	while (!ft_strchr(buff, '\n'))
	{
		ft_memset(buff, 0, 256 + 1);
		if ((ret = read(1, buff, 256)) < 0)
			break ;
		tmp = *line;
		(*line) = ft_strjoin(*line, buff);
		free(tmp);
		if ((tmp = ft_strchr(*line, '\n')))
			*tmp = 0;
	}
	return (ret);
}
