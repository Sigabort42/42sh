#include "lexer.h"
#include <stdlib.h>

char		*return_double_operator(int id)
{
	if (id == ID_OR)
		return (ft_strdup("||"));
	if (id == ID_AND)
		return (ft_strdup("&&"));
	if (id == ID_HEREDOC)
		return (ft_strdup("<<"));
	if (id == ID_APPEND)
		return (ft_strdup(">>"));
	if (id == ID_AG_LEFT)
		return (ft_strdup("<&"));
	if (id == ID_AG_RIGHT)
		return (ft_strdup(">&"));
	return (NULL);
}

void		fusion_single_operator(t_token **token)
{
	t_token	*tmp;
	t_token	*save;

	tmp = *token;
	if (tmp->next && tmp->next->id == tmp->id)
	{
		save = tmp->next->next;
		delete_token(&(tmp->next));
		tmp->next = save;
		if (save)
			save->prev = tmp;
		free(tmp->content);
		tmp->id += 5;
		tmp->content = return_double_operator(tmp->id);
	}
}

void		delete_separator_token(t_token **token)
{
	t_token	*tmp;
	t_token	*save;

	tmp = *token;
	while (tmp)
	{
		if (tmp->id == ID_SEPARATOR)
		{
			save = tmp->next;
			if (tmp->prev)
				tmp->prev->next = save;
			else
				*token = save;
			if (save)
				save->prev = tmp->prev;
			delete_token(&tmp);
			tmp = save;
		}
		else
			tmp = tmp->next;
	}
}

void		delete_null_token(t_token **token)
{
	t_token	*tmp;
	t_token	*prev;

	tmp = *token;
	if ((*token)->id == ID_NULL)
	{
		delete_token(token);
		*token = NULL;
		token = NULL;
		return ;
	}
	while (tmp->next)
		tmp = tmp->next;
	prev = tmp->prev;
	delete_token(&tmp);
	if (prev)
		prev->next = NULL;
}

void		fusion_aggregator(t_token **first, t_token **token)
{
	t_token	*tmp;
	t_token	*save;

	tmp = *token;
	if (tmp->next && tmp->next->id == ID_BG)
	{
		save = tmp->next->next;
		delete_token(&(tmp->next));
		tmp->next = save;
		if (save)
			save->prev = tmp;
		free(tmp->content);
		tmp->id += 7;
		tmp->content = return_double_operator(tmp->id);
	}
	if (tmp->id == ID_AG_LEFT || tmp->id == ID_AG_RIGHT ||
			tmp->id == ID_RED_RIGHT || tmp->id == ID_RED_LEFT ||
				tmp->id == ID_APPEND)
		add_fd_left_redir(first, &tmp);
}
