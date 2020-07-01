#include "builtin.h"
#include "../../libft/libft.h"
#include "error.h"

static void	fill_options(char c, int *options, const char *builtin_options)
{
	int	i;
	int	index;

	i = 0;
	index = 0;
	while (builtin_options[i])
	{
		if (c == builtin_options[i])
		{
			index = ft_recursive_power(2, i);
			*options |= index;
			return ;
		}
		i++;
	}
}

static char	check_options(char *str, int *options, const char *builtin_options)
{
	int	i;

	i = 0;
	if (str[i] == '-' && (++i))
	{
		if (!(str[i]))
			return (PARSER_CHK_FILE);
		if (str[i] == '-' && ft_strlen(str) == 2)
			return (PARSER_OP_END);
		while (str[i])
		{
			if (!ft_strchr(builtin_options, str[i]))
				return (str[i]);
			fill_options(str[i], options, builtin_options);
			i++;
		}
	}
	else
		return (PARSER_CHK_FILE);
	return (0);
}

char		check_args(char ***args, int *options, const char *builtin_options)
{
	int	i;
	int	ret;

	i = 1;
	while ((*args)[i])
	{
		ret = check_options((*args)[i], options, builtin_options);
		if (ret == PARSER_OP_END && (i++))
			break ;
		if (ret == PARSER_CHK_FILE)
			break ;
		if (ret > 0)
			return (ret);
		i++;
	}
	(*args) += i;
	return (0);
}
