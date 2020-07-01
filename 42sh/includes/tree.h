#ifndef TREE_H
# define TREE_H
# include "lexer.h"
# define HERDOC_FILE			".herdoc_file"

typedef struct					s_tree
{
	struct s_tree				*parent;
	t_token						*node;
	struct s_tree				*left;
	struct s_tree				*right;
	struct s_shell				*shell;
}								t_tree;

void							construct_tree(t_tree **tree, int s);
t_tree							*new_tree(void);
void							free_tree(t_tree *root);

#endif
