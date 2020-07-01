#include "lexer.h"

static	int		fill_fd_left(t_token *token)
{
	char	buffer[LINE_MAX];
	int		fd;

	fd = -1;
	ft_memset(buffer, 0, LINE_MAX);
	ft_strcat(buffer, token->content);
	if (token->id == ID_RED_LEFT || token->id == ID_RED_RIGHT)
	{
		if (ft_strlen(buffer) > 1)
		{
			ft_memset(buffer + ft_strlen(buffer) - 1, 0, 1);
			fd = ft_atoi(buffer);
		}
	}
	if (token->id == ID_AG_LEFT || token->id == ID_HEREDOC ||
			token->id == ID_AG_RIGHT || token->id == ID_APPEND)
	{
		if (ft_strlen(buffer) > 2)
		{
			ft_memset(buffer + ft_strlen(buffer) - 2, 0, 2);
			fd = ft_atoi(buffer);
		}
	}
	return (fd);
}

static	void	fill_redir(t_redir *redir, t_token *token)
{
	redir->left_fd = fill_fd_left(token);
	if (redir->left_fd == -1)
	{
		if (redir->id == ID_RED_RIGHT || redir->id == ID_APPEND)
			redir->left_fd = 1;
		else if (redir->id == ID_RED_LEFT || redir->id == ID_HEREDOC)
			redir->left_fd = 0;
		if (redir->id == ID_AG_RIGHT)
			redir->left_fd = REDIR_AG_1_2;
	}
	if (token->next)
	{
		if (redir->id == ID_AG_RIGHT)
		{
			if (ft_strcmp(token->next->content, "-") == 0)
				redir->right_fd = REDIR_AG_CLOSE;
			else if (ft_str_isdigit(token->next->content))
				redir->right_fd = ft_atoi(token->next->content);
			else
				redir->file = ft_strdup(token->next->content);
		}
		else
			redir->file = ft_strdup(token->next->content);
	}
}

void			redir_push_back(t_redir **list, t_redir *elem)
{
	t_redir	*tmp;

	tmp = *list;
	if (*list == NULL)
	{
		*list = elem;
		return ;
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = elem;
	elem->prev = tmp;
}

t_redir			*new_redir(t_token *token)
{
	t_redir	*elem;

	if (!(elem = malloc(sizeof(t_redir))))
		return (NULL);
	elem->id = token->id;
	elem->left_fd = -1;
	elem->right_fd = -1;
	elem->file = NULL;
	elem->prev = NULL;
	elem->next = NULL;
	fill_redir(elem, token);
	return (elem);
}
