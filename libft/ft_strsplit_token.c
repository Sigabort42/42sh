#include "libft.h"
#include <stdlib.h>
#include <stdio.h>

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

static int	is_quote(char s)
{
	const char	*brackets = "\"\'";
	int			i;

	i = 0;
	while (brackets[i])
	{
		if (s == brackets[i])
			return (1);
		i++;
	}
	return (0);
}

static int	count_words(char *str, char *c)
{
	int		word;
	int		is_word;
	char	*quote;

	word = 0;
	is_word = 0;
	quote = 0;
	while (*str != 0)
	{
		quote = (is_quote(*str) && quote == 0) ? str : quote;
		quote = (quote && (*str == *quote && str != quote)) ? 0 : quote;
		if (*str && !is_char(*str, c) && is_word == 0)
			is_word = 1;
		if (*str && is_char(*str, c) && is_word == 1 && quote == 0)
		{
			is_word = 0;
			word++;
		}
		str++;
	}
	return ((word += is_word));
}

static char	*get_word(char **s, char *c)
{
	char		*dup;
	char		*q;
	int			j;

	j = 0;
	q = 0;
	while (**s)
	{
		if (**s && !is_char(**s, c))
		{
			while (*(*s + j))
			{
				q = (is_quote(*(*s + j)) && q == 0) ? (*s) + j : q;
				q = (q && (*(*s + j) == *q && (*s) + j != q)) ? 0 : q;
				if (is_char(*(*s + j), c) && q == 0)
					break ;
				j++;
			}
			dup = ft_strndup(*s, j, 0);
			*s += j;
			return (dup);
		}
		(*s)++;
	}
	return (NULL);
}

char		**ft_strsplit_token(char *s, char *c)
{
	char		**tab;
	char		*str;
	int			i;
	int			size;

	i = 0;
	str = s;
	size = count_words(str, c);
	if (!str)
		return (NULL);
	if (!(tab = malloc(sizeof(char*) * (size + 1))))
		return (NULL);
	while (i < size)
	{
		tab[i] = get_word(&str, c);
		i++;
	}
	tab[i] = 0;
	return (tab);
}
