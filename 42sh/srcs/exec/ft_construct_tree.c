#include "tree.h"
#include <stdlib.h>

static	void	add_node(t_tree *tree, t_token *node)
{
	tree->node = node;
	tree->left = (t_tree*)malloc(sizeof(t_tree));
	tree->left->node = node->prev;
	tree->left->node->next = 0;
	tree->left->left = 0;
	tree->left->right = 0;
	tree->left->parent = tree;
	tree->right = (t_tree*)malloc(sizeof(t_tree));
	tree->right->node = node->next;
	tree->right->node->prev = 0;
	tree->right->right = 0;
	tree->right->left = 0;
	tree->right->parent = tree;
}

static	t_token	*search_operators(t_tree *tree, int operators, int s)
{
	t_token	*tmp;

	tmp = tree->node;
	if (!s)
	{
		while (tmp)
		{
			if (tmp && check_op_group(operators, tmp->id))
				return (tmp);
			tmp = tmp->next;
		}
	}
	else
	{
		while (tmp)
		{
			if (tmp && check_op_group(operators, tmp->id))
				return (tmp);
			tmp = tmp->prev;
		}
	}
	return (0);
}

void			construct_tree(t_tree **tree, int s)
{
	t_token	*node;

	if ((node = search_operators(*tree, ID_SEMICOLON, s)))
	{
		add_node(*tree, node);
		construct_tree(&(*tree)->left, 1);
		construct_tree(&(*tree)->right, 0);
	}
	else if ((node = search_operators(*tree, ID_AND_OR, s)))
	{
		add_node(*tree, node);
		construct_tree(&(*tree)->left, 1);
		construct_tree(&(*tree)->right, 0);
	}
	else if ((node = search_operators(*tree, ID_PIPE_CHECK, s)))
	{
		add_node(*tree, node);
		construct_tree(&(*tree)->left, 1);
		construct_tree(&(*tree)->right, 0);
	}
}
