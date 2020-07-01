#ifndef LEXER_H
# define LEXER_H

# include <limits.h>
# include <fcntl.h>
# include "../../libft/libft.h"

# define STATE_NULL			0
# define STATE_WRITE		1
# define STATE_FINISH		2

# define ID_PIPE			0
# define ID_BG				1
# define ID_RED_LEFT		2
# define ID_RED_RIGHT		3
# define ID_SEMICOLON		4
# define ID_OR				5
# define ID_AND				6
# define ID_HEREDOC			7
# define ID_APPEND			8
# define ID_AG_LEFT			9
# define ID_AG_RIGHT		10
# define ID_WORD			11
# define ID_SEPARATOR		12
# define ID_NULL			13

# define ID_AND_OR			1
# define ID_REDIRECTION		2
# define ID_PIPE_CHECK		3
# define ID_REDIRECTION_R	4
# define ID_REDIRECTION_L	5
# define ID_AGGREGATOR		6

# define REDIR_AG_CLOSE		-2
# define REDIR_AG_1_2		-3

typedef struct		s_redir
{
	int				id;
	int				left_fd;
	int				right_fd;
	char			*file;
	struct s_redir	*prev;
	struct s_redir	*next;
}					t_redir;

typedef struct		s_token
{
	int				id;
	char			*content;
	t_redir			*redir;
	struct s_token	*prev;
	struct s_token	*next;
}					t_token;

/*
**					struct: token
*/
t_token				*new_token(int id, char *content);
void				delete_token(t_token **token);
void				free_single_token(t_token *token);
void				free_token_list(t_token *token);
void				init_first(t_token **token);
/*
**					struct: redir
*/
t_redir				*new_redir(t_token *token);
void				redir_push_back(t_redir **list, t_redir *elem);
/*
**					lexer
*/
t_token				*tokenizer(char *input);
int					fusion_operator(t_token **token);
void				fusion_single_operator(t_token **token);
void				fusion_aggregator(t_token **first, t_token **token);
void				add_fd_left_redir(t_token **first, t_token **token);
void				replace_redir(t_token **token);
void				delete_separator_token(t_token **token);
void				delete_null_token(t_token **token);
void				fusion_word(t_token **token);
char				*return_double_operator(int id);
/*
**					parsing
*/
int					check_tokens(t_token *list);
int					parse_complete_line(t_token *list);
/*
**					check functions
*/
int					check_id(char c);
char				is_quote(char c);
int					is_token_operator(int token_id);
int					check_op_group(int operators, int id);
/*
**					debug functions
*/
void				print_token_list(t_token *token);
void				print_token_list_reverse(t_token *token);
#endif
