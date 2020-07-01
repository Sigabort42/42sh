#include "lexer.h"
#include "libft.h"

void		print_token_list(t_token *token)
{
	t_token	*tmp;
	t_redir	*tmp_redir;

	tmp = token;
	ft_putendl("---------- tokens:");
	while (tmp)
	{
		tmp_redir = tmp->redir;
		ft_putnbr(tmp->id);
		ft_putstr(" - ");
		ft_putendl(tmp->content ? tmp->content : "null");
		while (tmp_redir)
		{
			ft_putstr("-> redir: left_fd: ");
			ft_putnbr(tmp_redir->left_fd);
			ft_putstr(" - right_fd: ");
			ft_putnbr(tmp_redir->right_fd);
			ft_putstr(" - ");
			ft_putendl(tmp_redir->file ? tmp_redir->file : "null");
			tmp_redir = tmp_redir->next;
		}
		tmp = tmp->next;
	}
}

void		print_token_list_reverse(t_token *token)
{
	t_token	*tmp;

	tmp = token;
	ft_printf("---------- reverse:\n");
	while (tmp->next)
		tmp = tmp->next;
	while (tmp)
	{
		ft_printf("%d - %s\n", tmp->id, tmp->content);
		tmp = tmp->prev;
	}
}
