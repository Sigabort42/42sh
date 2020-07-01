#include "builtin.h"
#include "../../libft/libft.h"
#include "error.h"
#include <stdio.h>

static void	ft_echo_check_opt(char ***args, int *options)
{
	int	i;

	i = 1;
	while ((*args)[i])
	{
		if (ft_strcmp((*args)[i], "-n") == 0)
			*options |= ECHO_OP_N;
		else
			break ;
		i++;
	}
	(*args) += i;
}

static int	ft_print_value(t_env *list, char *str)
{
	t_env	*env;
	int		len;

	len = 0;
	env = ft_getenv(list, str + 1);
	if (str[0] == '$')
	{
		if (env)
			len = ft_putstr(env->value);
	}
	else
		len = ft_putstr(str);
	return (len);
}

int			ft_builtin_echo(t_env *list, t_process *prog)
{
	int		i;
	int		options;
	int		len;

	i = 0;
	options = 0;
	ft_echo_check_opt(&(prog->args), &options);
	while (prog->args[i])
	{
		len = ft_print_value(list, prog->args[i]);
		if (prog->args[i + 1] && len)
			ft_putstr(" ");
		i++;
	}
	if (!IS_OP(options, ECHO_OP_N))
		ft_putstr("\n");
	return (0);
}
