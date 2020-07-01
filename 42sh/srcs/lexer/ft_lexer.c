#include "lexer.h"

static void	create_token(t_token **token, char *token_buffer, int *state)
{
	(*token)->content = ft_strdup(token_buffer);
	ft_memset(token_buffer, 0, LINE_MAX);
	(*token)->next = new_token(ID_NULL, NULL);
	(*token)->next->prev = *token;
	*token = (*token)->next;
	*state = STATE_NULL;
}

static void	bool_quote(char **quote, char *s)
{
	*quote = (is_quote(*s) && *quote == 0) ? s : *quote;
	*quote = (is_quote(*s) && **quote == is_quote(*s) && *quote != s) ?
		0 : *quote;
}

static void	state_write(char **s, char *buf, t_token *token, int *state)
{
	ft_strncat(buf, (*s)++, 1);
	if (is_token_operator(token->id) != -1)
		*state = STATE_FINISH;
}

t_token		*tokenizer(char *s)
{
	t_token	*token;
	t_token	*first;
	char	token_buffer[LINE_MAX];
	char	*q;
	int		state;

	token = new_token(ID_NULL, NULL);
	first = token;
	ft_memset(token_buffer, 0, LINE_MAX);
	q = 0;
	state = STATE_NULL;
	while (*s)
	{
		token->id = (token->id == ID_NULL) ? check_id(*s) : token->id;
		state = (token->id != ID_NULL) ? STATE_WRITE : state;
		state = (check_id(*s) != token->id && q == 0) ? STATE_FINISH : state;
		bool_quote(&q, s);
		if (state == STATE_WRITE)
			state_write(&s, token_buffer, token, &state);
		if (state == STATE_FINISH)
			create_token(&token, token_buffer, &state);
	}
	if (state == STATE_WRITE)
		create_token(&token, token_buffer, &state);
	return (first);
}
