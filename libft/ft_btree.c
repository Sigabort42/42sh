#include "./includes/btree.h"

int				ft_search_node(t_btree *tree, void *data[], int type)
{
	while (tree)
	{
		if (type == 0)
		{
			if ((int)data[0] == (int)tree->data[0])
				return (0);
			if ((int)data[0] > (int)tree->data[0])
				tree = tree->right;
			else
				tree = tree->left;
		}
		else
		{
			if (!ft_strcmp((char*)data[0], (char*)tree->data[0]))
				return (0);
			if (ft_strcmp((char*)data[0], (char*)tree->data[0]) > 0)
				tree = tree->right;
			else
				tree = tree->left;
		}
	}
	return (1);
}

void			ft_print_tree(t_btree *tree)
{
	if (!tree)
		return ;
	if (tree->left)
		ft_print_tree(tree->left);
	ft_printf("data[0]%s| data[1]%s| data[2]%s|\n", (char*)tree->data[0],
			(char*)tree->data[1], (char*)tree->data[2]);
	if (tree->right)
		ft_print_tree(tree->right);
}

void			ft_clear_tree(t_btree **tree)
{
	t_btree		*tmp_tree;

	tmp_tree = *tree;
	if (*tree)
		return ;
	if (tmp_tree->left)
		ft_clear_tree(&tmp_tree->left);
	if (tmp_tree->right)
		ft_clear_tree(&tmp_tree->right);
	free(tmp_tree);
	*tree = 0;
}
