#include "manage_line.h"
#include <term.h>

void		replace_var_env(t_shell *shell, char **str, char **ev, int *i)
{
	char	*stack;
	char	*end;
	char	*tmp;

	if (shell->states[*i] == '1')
	{
		ft_strcut(str, *i - 1, 1);
		return ;
	}
	stack = NULL;
	tmp = get_name(*str + *i + 1);
	if (ft_search_var_env(ev, tmp) != -1)
		stack = ev[ft_search_var_env(ev, tmp)] +
			ft_strlen(tmp) + 1;
	end = ft_strdup(*str + *i + ft_strlen(tmp) + 1);
	if (*i > 0)
		*str = ft_strndup(*str, *i, 1);
	else
		ft_strdel(str);
	*str = ft_strjoin_free(*str, ft_strdup(stack));
	*str = ft_strjoin_free(*str, end);
	ft_strdel(&tmp);
}

void		change_var_env(t_shell *shell, char **str, char **ev)
{
	int		i;

	i = 0;
	while (i < (int)ft_strlen(*str))
	{
		if ((*str)[i] == '"' && (i++))
		{
			while ((*str)[i] && (*str)[i] != '\"')
			{
				if ((*str)[i] == '$')
					replace_var_env(shell, str, ev, &i);
				i++;
			}
		}
		else if ((*str)[i] == '\'' && (i++))
		{
			while ((*str)[i] && (*str)[i] != '\'')
				i++;
		}
		else if ((*str)[i] == '$')
			replace_var_env(shell, str, ev, &i);
		i++;
	}
}
