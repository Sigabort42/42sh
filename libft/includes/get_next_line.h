#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define BUFF_SIZE 42
# include <fcntl.h>

typedef struct	s_varia
{
	int			ret;
	char		*tab[4096];
	char		*rst;
	char		buf[BUFF_SIZE];
}				t_varia;

int				get_next_line(int fd, char **line);

#endif
