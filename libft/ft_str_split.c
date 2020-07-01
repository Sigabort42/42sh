#include "libft.h"
#include <stdlib.h>

static int	is_char(char s, char *c)
{
	int	i;

	i = 0;
	while (c[i])
	{
		if (s == c[i])
			return (1);
		i++;
	}
	return (0);
}

static int	count_words(char *str, char *c)
{
	int i;
	int word;
	int is_word;

	i = 0;
	word = 0;
	is_word = 0;
	while (str[i])
	{
		if (str[i] && !is_char(str[i], c) && is_word == 0)
			is_word = 1;
		if (str[i] && is_char(str[i], c) && is_word == 1)
		{
			is_word = 0;
			word++;
		}
		i++;
	}
	if (is_word == 1)
		word++;
	return (word);
}

static char	*get_word(char *str, char *c, int *i)
{
	char		*dup;
	int			j;

	j = 0;
	while (str[(*i)])
	{
		if (str[(*i)] && !is_char(str[(*i)], c))
		{
			while (str[(*i) + j] && !is_char(str[(*i) + j], c))
				j++;
			dup = ft_strndup(str + (*i), j, 0);
			(*i) += j;
			return (dup);
		}
		(*i)++;
	}
	return (NULL);
}

char		**ft_str_split(char *s, char *c)
{
	char		**tab;
	int			i;
	int			j;
	int			size;

	i = 0;
	j = 0;
	size = count_words(s, c);
	if (!s)
		return (NULL);
	if (!(tab = malloc(sizeof(char*) * (size + 1))))
		return (NULL);
	while (i < size)
	{
		tab[i] = get_word(s, c, &j);
		i++;
	}
	tab[i] = 0;
	return (tab);
}
