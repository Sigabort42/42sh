#include "builtin.h"
#include "../../libft/libft.h"

int		option_less(t_env *list, char **dir)
{
	if (ft_strcmp(*dir, "-") == 0)
	{
		if (ft_getenv(list, "OLDPWD"))
			*dir = ft_getenv(list, "OLDPWD")->value;
		else
			return (1);
	}
	return (0);
}

void	set_pwd(t_env **list, char *path)
{
	if (ft_getenv(*list, "PWD"))
		ft_setenv(list, "OLDPWD", ft_getenv(*list, "PWD")->value, 1);
	ft_setenv(list, "PWD", path, 1);
}
