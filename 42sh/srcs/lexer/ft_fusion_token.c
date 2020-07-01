#include "lexer.h"
#include <stdlib.h>
#include <stdio.h>

int			fusion_operator(t_token **token)
{
	t_token	*tmp;

	tmp = *token;
	while (tmp)
	{
		if (tmp->id >= ID_PIPE && tmp->id <= ID_RED_RIGHT)
			fusion_single_operator(&tmp);
		if (tmp->id >= ID_RED_LEFT && tmp->id <= ID_RED_RIGHT)
			fusion_aggregator(token, &tmp);
		tmp = tmp->next;
	}
	delete_separator_token(token);
	if (check_tokens(*token) != 0)
		return (-1);
	replace_redir(token);
	fusion_word(token);
	if (parse_complete_line(*token) != 0)
		return (-1);
	fusion_word(token);
	delete_null_token(token);
	return (0);
}

static void	buff_word(t_token *first, t_token *token,
				t_token **last, char *buffer)
{
	t_token	*tmp;

	if (token->id == ID_WORD)
	{
		ft_strcat(buffer, token->content);
		if (token->next)
			if (token->next->id == ID_WORD)
				ft_strcat(buffer, " ");
		tmp = token->next;
		if (token != first)
			delete_token(&token);
		buff_word(first, tmp, last, buffer);
	}
	else
	{
		*last = token;
		return ;
	}
}

static void	merge_word(t_token *token, char *buffer)
{
	t_token	*last;
	t_token	*tmp;

	tmp = token;
	buff_word(tmp, tmp, &last, buffer);
	free(tmp->content);
	tmp->content = ft_strdup(buffer);
	tmp->next = last;
	last->prev = tmp;
	ft_memset(buffer, 0, LINE_MAX);
}

static void	merge_redirection(t_token *token)
{
	t_token	*first;
	t_token	*tmp;
	t_token	*save;

	first = token;
	tmp = token->next;
	while (tmp)
	{
		save = (tmp->next) ? tmp->next->next : NULL;
		if (check_op_group(ID_REDIRECTION, tmp->id))
		{
			redir_push_back(&(first->redir), new_redir(tmp));
			delete_token(&(tmp->next));
			delete_token(&tmp);
			first->next = save;
			if (save)
				save->prev = first;
		}
		else
			break ;
		tmp = save;
	}
}

void		fusion_word(t_token **token)
{
	char	buffer[LINE_MAX];
	t_token	*tmp;

	ft_memset(buffer, 0, LINE_MAX);
	tmp = *token;
	while (tmp)
	{
		if (tmp->id == ID_WORD)
			merge_word(tmp, buffer);
		if (tmp->next && check_op_group(ID_REDIRECTION, tmp->next->id))
			merge_redirection(tmp);
		tmp = tmp->next;
	}
}
