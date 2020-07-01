#include "lexer.h"
#include <stdio.h>

static int	ft_usage_pars(t_token *tmp)
{
	ft_putstr_fd("42sh: parse error near \'", 2);
	ft_putstr_fd(tmp->content, 2);
	ft_putendl_fd("\'", 2);
	return (-1);
}

int			check_tokens(t_token *list)
{
	t_token	*tmp;

	tmp = list;
	while (tmp)
	{
		if (tmp->id >= 0 && tmp->id <= 8)
		{
			if ((tmp->prev && (tmp->prev->id != ID_WORD ||
					tmp->prev->id == ID_NULL)) || tmp->prev == NULL)
				return (ft_usage_pars(tmp));
			if ((tmp->next && (tmp->next->id != ID_WORD ||
					tmp->next->id == ID_NULL)) || tmp->next == NULL)
				return (ft_usage_pars(tmp));
		}
		if (tmp->id == ID_AG_RIGHT || tmp->id == ID_AG_LEFT)
		{
			if ((tmp->next && (tmp->next->id != ID_WORD ||
					tmp->next->id == ID_NULL)) || tmp->next == NULL)
				return (ft_usage_pars(tmp));
		}
		tmp = tmp->next;
	}
	return (0);
}

int			parse_complete_line(t_token *list)
{
	t_token	*tmp;

	tmp = list;
	while (tmp)
	{
		if (tmp->id >= 0 && tmp->id <= 10)
		{
			if ((tmp->prev && (tmp->prev->id != ID_WORD ||
					tmp->prev->id == ID_NULL)) || tmp->prev == NULL)
				return (ft_usage_pars(tmp));
			if ((tmp->next && (tmp->next->id != ID_WORD ||
					tmp->next->id == ID_NULL)) || tmp->next == NULL)
				return (ft_usage_pars(tmp));
		}
		tmp = tmp->next;
	}
	return (0);
}
