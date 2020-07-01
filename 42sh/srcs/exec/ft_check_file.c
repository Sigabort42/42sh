#include "libft.h"
#include "exec.h"
#include "error.h"

static int	check_file_access(char *file, int tmp_id)
{
	t_stat	info;
	int		ret;

	ret = 0;
	if ((ret = stat(file, &info)) != 0 &&
				(tmp_id == ID_RED_LEFT || tmp_id == ID_HEREDOC))
		return (ft_usage_file(FILE_NOT_FOUND, file));
	else if (S_ISDIR(info.st_mode))
		return (ft_usage_file(FILE_IS_DIR, file));
	else if ((ret = access(file, R_OK)) != 0)
		return (ft_usage_file(FILE_NOT_ACCESS, file));
	return (ret);
}

static void	open_file(t_redir *tmp)
{
	if (tmp->id == ID_RED_RIGHT || tmp->id == ID_APPEND ||
			tmp->id == ID_AG_RIGHT)
	{
		if (tmp->file)
		{
			if (tmp->id == ID_APPEND)
				tmp->right_fd =
					open(tmp->file, O_RDWR | O_CREAT | O_APPEND, 0644);
			else
				tmp->right_fd =
					open(tmp->file, O_RDWR | O_CREAT | O_TRUNC, 0644);
			if (tmp->right_fd == -1)
				check_file_access(tmp->file, tmp->id);
		}
	}
	else if (tmp->id == ID_RED_LEFT || tmp->id == ID_HEREDOC)
	{
		if (check_file_access(tmp->file, tmp->id) == 0)
			tmp->right_fd = open(tmp->file, O_RDWR);
	}
}

void		ft_check_file(t_tree *root)
{
	t_redir	*tmp;

	if (root->node->id == ID_WORD)
	{
		tmp = root->node->redir;
		while (tmp)
		{
			open_file(tmp);
			tmp = tmp->next;
		}
	}
	if (root->left)
		ft_check_file(root->left);
	if (root->right)
		ft_check_file(root->right);
}
