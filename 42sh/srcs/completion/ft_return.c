#include "completion.h"

static int			ft_return_for_one(t_comp *comp, char *ret, char *s)
{
	ft_strcat(s, comp->line);
	ft_strcat(s, ret);
	if (comp->after)
		ft_strcat(ft_strcat(s, " "), comp->after);
	return (ft_strlen(ret));
}

int					final_return(t_shell *sh, t_comp *cp, char **ret, int csr)
{
	char	*s;
	int		len;

	s = ft_strnew(PATH_MAX);
	len = 0;
	if (ft_tablen(ret) == 1)
		len = ft_return_for_one(cp, ret[0], s);
	else
	{
		ft_strcat(s, cp->line);
		prepare_ret(sh, cp, ret);
		if (cp->after)
			ft_strcat(ft_strcat(s, " "), cp->after);
	}
	if (ft_tablen(ret) == 1 && cp->type == 1)
		cp->buf[0] = ft_strjoin_free(cp->buf[0], ft_strdup(ret[0]));
	else
	{
		free(sh->tab_history[sh->line]);
		sh->tab_history[sh->line] = ft_strdup(s);
	}
	free(s);
	if ((cp->after && ft_tablen(ret) != 1) || ft_tablen(ret) != 1)
		return (csr);
	return (csr + len);
}
