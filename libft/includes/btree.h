#ifndef BTREE_H
# define BTREE_H
# include "./../ft_printf/ft_printf.h"

typedef struct		s_btree
{
	void			*data[3];
	struct s_btree	*left;
	struct s_btree	*right;
}					t_btree;

int					ft_btree_add_node(t_btree **tree, void *data[], int type);
int					ft_search_node(t_btree *tree, void *data[], int type);
void				ft_print_tree(t_btree *node);
void				ft_clear_tree(t_btree **tree);

#endif
