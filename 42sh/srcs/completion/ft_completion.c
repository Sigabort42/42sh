#include "completion.h"

static char		**one_result(char **add, t_comp *cp)
{
	if (!(add = (char**)ft_memalloc(sizeof(char*) * 2)))
		return (NULL);
	add[1] = NULL;
	if (cp->case_ > 2)
	{
		if (cp->start)
			add[0] = ft_strdup(cp->lst->name + ft_strlen(cp->start) - 1);
		else
			add[0] = ft_strdup(cp->lst->name);
	}
	else
		add[0] = ft_strdup(cp->lst->name + ft_strlen(cp->start));
	if (add[0] && cp->lst->isdir)
		add[0] = ft_strjoin_free(add[0], ft_strdup("/"));
	if (!add[0])
		return (NULL);
	return (add);
}

static char		*find_start(const int case_, t_token *first)
{
	if (!first)
		return (NULL);
	if (case_ == PRINT_FILE || case_ == PRINT_CMD)
		return (NULL);
	while (first->next && first->id != 13)
		first = first->next;
	if (first->prev)
		first = first->prev;
	return (ft_strdup(first->content));
}

static char		**do_completion(const t_shell *shell, t_comp *cp)
{
	char		**ret;
	int			case_;

	ret = NULL;
	if (!(cp->first = tokenizer(cp->line)))
		return (NULL);
	if ((cp->case_ = find_case(cp->first)) == -1)
		return (NULL);
	case_ = cp->case_;
	cp->start = find_start(cp->case_, cp->first);
	if (case_ > 2 && !(cp->lst = do_it_file(cp, shell->init.evp)))
		return (NULL);
	else if (case_ < 3 && !(cp->lst = do_it_cmd(cp->start, shell->init.evp)))
		return (NULL);
	cp->lst = opti_ret(cp->start, cp->lst);
	if (cp->lst && !cp->lst->next)
		ret = one_result(ret, cp);
	else if (cp->lst && cp->lst->next)
		ret = lst_to_tab(ret, cp->lst);
	return (ret);
}

void			find_line_after(t_shell *shell, t_comp *cp, int csr, char **buf)
{
	int		tmp;

	tmp = csr - shell->f_len;
	cp->type = 0;
	if (ft_strcmp(shell->tab_history[shell->line], *buf) != 0)
	{
		tmp += ft_strlen(shell->tab_history[shell->line]);
		cp->buf = buf;
		cp->line = ft_strjoin(shell->tab_history[shell->line], *buf);
		cp->type = 1;
	}
	else
		cp->line = ft_strdup(shell->tab_history[shell->line]);
	if (tmp < (int)ft_strlen(cp->line))
	{
		cp->after = cp->line + tmp + 1;
		cp->line[tmp] = '\0';
	}
}

int				ft_completion(t_shell *shell, char **buf, int csr)
{
	t_comp		*comp;
	char		**ret;

	if ((comp = (t_comp*)ft_memalloc(sizeof(t_comp)))
		&& shell->tab_history[shell->line] && buf)
	{
		find_line_after(shell, comp, csr, buf);
		if ((ret = do_completion(shell, comp)))
		{
			csr = final_return(shell, comp, ret, csr);
			ft_refresh_line(shell, shell->tab_history[shell->line], csr);
			ft_tabdel(ret);
		}
	}
	if (comp)
	{
		free(comp->line);
		if (comp->start)
			free(comp->start);
		free_token_list(comp->first);
		my_free_lst(comp->lst);
		free(comp);
	}
	return (csr);
}
