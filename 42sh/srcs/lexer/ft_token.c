#include "lexer.h"
#include <stdlib.h>

t_token	*new_token(int id, char *content)
{
	t_token	*elem;

	if (!(elem = malloc(sizeof(t_token))))
		return (NULL);
	elem->id = id;
	elem->content = content;
	elem->redir = NULL;
	elem->next = NULL;
	elem->prev = NULL;
	return (elem);
}

void	delete_token(t_token **token)
{
	t_redir	*tmp_redir;

	free((*token)->content);
	(*token)->prev = NULL;
	(*token)->next = NULL;
	while ((*token)->redir)
	{
		tmp_redir = (*token)->redir->next;
		if ((*token)->redir->file)
			free((*token)->redir->file);
		free((*token)->redir);
		(*token)->redir = tmp_redir;
	}
	free(*token);
	(*token) = NULL;
}

void	free_single_token(t_token *token)
{
	t_token	*tmp;
	t_redir	*tmp_redir;

	tmp = token;
	while (tmp->redir)
	{
		tmp_redir = tmp->redir->next;
		if (tmp->redir->file)
			free(tmp->redir->file);
		free(tmp->redir);
		tmp->redir = tmp_redir;
	}
	if (tmp->content)
		free(tmp->content);
	free(tmp);
}

void	free_token_list(t_token *token)
{
	t_token	*tmp;
	t_token	*tmp_next;

	tmp = token;
	while (tmp)
	{
		tmp_next = tmp->next;
		free_single_token(tmp);
		tmp = tmp_next;
	}
}
