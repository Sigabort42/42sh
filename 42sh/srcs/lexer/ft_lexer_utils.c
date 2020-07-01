#include "lexer.h"
#include "env.h"

int		check_id(char c)
{
	int	ret;
	int	i;

	i = 0;
	ret = -1;
	ret = (c == '|') ? ID_PIPE : ret;
	ret = (c == '&') ? ID_BG : ret;
	ret = (c == '<') ? ID_RED_LEFT : ret;
	ret = (c == '>') ? ID_RED_RIGHT : ret;
	ret = (c == ';') ? ID_SEMICOLON : ret;
	ret = (c == ' ') ? ID_SEPARATOR : ret;
	ret = (c == '\n') ? ID_SEPARATOR : ret;
	ret = (c == '\t') ? ID_SEPARATOR : ret;
	ret = (c == 0) ? ID_NULL : ret;
	ret = (ret == -1) ? ID_WORD : ret;
	return (ret);
}

char	is_quote(char c)
{
	if (c == '\'' || c == '\"' || c == '`')
		return (c);
	return (0);
}

int		is_token_operator(int token_id)
{
	if (token_id >= ID_PIPE && token_id <= ID_AG_RIGHT)
		return (token_id);
	return (-1);
}

int		check_op_group(int operators, int id)
{
	if (operators == ID_AND_OR)
	{
		if (id == ID_AND || id == ID_OR)
			return (1);
	}
	if (operators == ID_REDIRECTION)
	{
		if (id == ID_RED_RIGHT || id == ID_APPEND || id == ID_RED_LEFT ||
			id == ID_HEREDOC || id == ID_AG_LEFT || id == ID_AG_RIGHT)
			return (2);
	}
	if (operators == ID_PIPE_CHECK)
	{
		if (id == ID_PIPE)
			return (3);
	}
	if (operators == ID_SEMICOLON)
	{
		if (id == ID_SEMICOLON)
			return (4);
	}
	return (0);
}
