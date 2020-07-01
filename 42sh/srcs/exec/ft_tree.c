#include "tree.h"
#include <stdlib.h>

t_tree	*new_tree(void)
{
	t_tree	*elem;

	if (!(elem = (t_tree*)malloc(sizeof(t_tree))))
		return (0);
	elem->parent = 0;
	elem->left = 0;
	elem->right = 0;
	elem->node = 0;
	elem->shell = 0;
	return (elem);
}

void	free_tree(t_tree *root)
{
	if (root->left)
		free_tree(root->left);
	if (root->right)
		free_tree(root->right);
	if (root->node)
		free_single_token(root->node);
	free(root);
}
