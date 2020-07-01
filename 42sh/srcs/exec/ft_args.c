#include "exec.h"
#include "../../libft/libft.h"
#include <stdlib.h>

void		free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		tab[i] = NULL;
		i++;
	}
	free(tab);
	tab = NULL;
}

static int	get_tab_size(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}

char		**duplicate_tab(char **args)
{
	char	**dup;
	int		i;

	i = 0;
	while (args[i])
		i++;
	dup = malloc(sizeof(char*) * (i + 1));
	i = 0;
	while (args[i])
	{
		dup[i] = ft_strdup(args[i]);
		i++;
	}
	dup[i] = NULL;
	return (dup);
}

void		delete_options_unused(char ***args, int index)
{
	char	**tab;
	int		i;
	int		size;

	i = index;
	size = get_tab_size(*args);
	tab = malloc(sizeof(char*) * ((size - index) + 1));
	while (index < size)
	{
		tab[i] = ft_strdup(*args[index]);
		i++;
		index++;
	}
	tab[i] = NULL;
	free_tab(*args);
	(*args) = tab;
}
