#include "libft.h"

t_list		*ft_lstpushparams(int argc, char **argv)
{
	size_t		i;
	t_list		*lst;
	t_list		*elem;

	i = 0;
	if (argc < 1)
		return (0);
	lst = ft_lstnew(argv[i], ft_strlen(argv[i]));
	i++;
	while (argv[i])
	{
		elem = ft_lstnew(argv[i], ft_strlen(argv[i]));
		ft_lstpushback(&lst, elem);
		i++;
	}
	return (lst);
}
