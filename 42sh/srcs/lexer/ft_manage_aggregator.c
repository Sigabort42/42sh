#include "lexer.h"
#include <stdlib.h>
#include <stdio.h>

void			add_fd_left_redir(t_token **first, t_token **token)
{
	t_token	*tmp;
	t_token	*save;
	char	*content_save;

	tmp = *token;
	if (tmp->prev && ft_str_isdigit(tmp->prev->content))
	{
		save = tmp->prev->prev;
		content_save = tmp->content;
		tmp->content = ft_strjoin(tmp->prev->content, tmp->content);
		free(content_save);
		delete_token(&(tmp->prev));
		tmp->prev = save;
		if (save)
			save->next = tmp;
		else
			*first = tmp;
	}
}

static t_token	*find_next_operator(t_token *token)
{
	t_token	*tmp;

	tmp = token;
	while (tmp)
	{
		if (is_token_operator(tmp->id) != -1 || tmp->id == ID_NULL)
		{
			if (tmp != token)
				return (tmp);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

static void		move_token(t_token **first, t_token **token,
					t_token *operator, t_token *next_token)
{
	t_token	*save;
	t_token	*next_prev_token;

	next_prev_token = next_token->prev;
	next_token->prev = (*token)->prev;
	if ((*token)->prev)
		(*token)->prev->next = next_token;
	else
		(*first) = next_token;
	save = operator->prev;
	operator->prev->next = (*token);
	if (next_token == (*token)->next)
		operator->prev = (*token);
	else
		operator->prev = next_prev_token;
	(*token)->prev = save;
	if (next_token == (*token)->next)
		(*token)->next = operator;
	else
		(*token)->next->next = operator;
}

static void		move_redir(t_token **first, t_token **token)
{
	t_token	*next_token;
	t_token	*operator;

	next_token = (*token)->next;
	if ((*token)->next && (*token)->next->id == ID_WORD)
		next_token = (*token)->next->next;
	operator = find_next_operator(*token);
	if (next_token == operator)
		return ;
	if (next_token)
		move_token(first, token, operator, next_token);
}

void			replace_redir(t_token **token)
{
	t_token	*tmp;
	t_token	*last;

	tmp = *token;
	while (tmp->next)
		tmp = tmp->next;
	last = tmp;
	while (tmp)
	{
		if (tmp->id == ID_AG_LEFT || tmp->id == ID_AG_RIGHT ||
				tmp->id == ID_RED_RIGHT || tmp->id == ID_RED_LEFT ||
					tmp->id == ID_APPEND)
			move_redir(token, &tmp);
		tmp = tmp->prev;
	}
}
