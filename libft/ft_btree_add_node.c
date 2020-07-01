#include "./includes/btree.h"

static void		ft_add_node_char(t_btree *tmp_node, t_btree *tmp_tree,
t_btree *node, char *data[])
{
	while (tmp_tree)
	{
		tmp_node = tmp_tree;
		if (ft_strcmp(data[0], (char*)tmp_tree->data[0]) < 0)
		{
			tmp_tree = tmp_tree->right;
			if (!tmp_tree)
				tmp_node->right = node;
		}
		else
		{
			tmp_tree = tmp_tree->left;
			if (!tmp_tree)
				tmp_node->left = node;
		}
	}
}

static void		ft_add_node_int(t_btree *tmp_node, t_btree *tmp_tree,
t_btree *node, int data[])
{
	while (tmp_tree)
	{
		tmp_node = tmp_tree;
		if (data[0] > (int)tmp_tree->data[0])
		{
			tmp_tree = tmp_tree->right;
			if (!tmp_tree)
				tmp_node->right = node;
		}
		else
		{
			tmp_tree = tmp_tree->left;
			if (!tmp_tree)
				tmp_node->left = node;
		}
	}
}

int				ft_btree_add_node(t_btree **tree, void *data[], int type)
{
	t_btree		*tmp_node;
	t_btree		*tmp_tree;
	t_btree		*node;

	tmp_node = 0;
	tmp_tree = *tree;
	if (!(node = malloc(sizeof(*node))))
		return (1);
	node->data[0] = data[0];
	node->data[1] = data[1];
	node->data[2] = data[2];
	node->left = 0;
	node->right = 0;
	if (!tmp_tree)
		*tree = node;
	else
	{
		if (type == 0)
			ft_add_node_int(tmp_node, tmp_tree, node, (int*)data);
		else
			ft_add_node_char(tmp_node, tmp_tree, node, (char**)data);
	}
	return (0);
}
