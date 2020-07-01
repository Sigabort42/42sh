#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include "./ft_printf/ft_printf.h"
# include "./includes/get_next_line.h"
# include "./includes/btree.h"

typedef struct		s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}					t_list;

void				ft_strcut(char **str, int start, int len);
void				ft_strpush(char **str, char *in, int start);
void				ft_strclr(char *s);
void				ft_strdel(char **as);
void				ft_striter(char *s, void (*f)(char *));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
int					ft_putstr(char const *s);
void				ft_putendl(char const *s);
void				ft_putnbr(int n);
void				ft_putnbr_fd(int n, int fd);
void				ft_putendl_fd(char const *s, int fd);
void				ft_putstr_fd(char const *s, int fd);
void				ft_putchar_fd(char c, int fd);
void				*ft_memset(void *b, int c, size_t len);
void				ft_bzero(void *s, size_t n);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				*ft_memccpy(void *dst, const void *src, int c, size_t n);
void				*ft_memchr(const void *s, int c, size_t n);
void				*ft_memmove(void *dst, const void *src, size_t len);
void				*ft_memalloc(size_t size);
void				ft_memdel(void **ap);
void				ft_lstadd(t_list **alst, t_list *new);
void				ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void				ft_lstdelone(t_list **alst, void (*del)(void *, size_t));
void				ft_lstiter(t_list *lst, void (*f)(t_list *elem));
void				ft_lstpushback(t_list **lst, t_list *elem);
int					ft_tablen(char **str2);
int					ft_count_char(char *str, char c);
int					ft_index(char *str, char c);
int					ft_strstart(char *str, char *start);
int					ft_isspace(char c);
int					ft_str_isdigit(char *str);
int					ft_recursive_power(int nb, int power);
int					ft_putchar(int c);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
int					ft_isalpha(int c);
int					ft_isalnum(int c);
int					ft_isdigit(int c);
int					ft_isascii(int c);
int					ft_isprint(int c);
int					ft_toupper(int c);
int					ft_tolower(int c);
int					ft_atoi(const char *str);
int					ft_strequ(char const *s1, char const *s2);
int					ft_strnequ(char const *s1, char const *s2, size_t n);
int					get_next_line(int fd, char **line);
int					ft_islower(int c);
int					ft_isupper(int c);
int					ft_issign(char c);
int					ft_isspace_word(char *s);
int					ft_intlen(int nb);
size_t				ft_lstcount(t_list *lst);
size_t				ft_strlen(const char *s);
size_t				ft_strlcat(char *dst, const char *src, size_t size);
t_list				*ft_lstnew(void const *content, size_t content_size);
t_list				*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
t_list				*ft_lstlast(t_list *lst);
t_list				*ft_lstpushparams(int argc, char **argv);
char				*ft_getword(char *str);
char				*ft_concat_tab(char **to_str, char *delim);
char				*ft_strcdup(char *s1, int c);
char				*ft_strrev(char *str);
char				*ft_strjoin_free(char *s1, char *s2);
char				*ft_split(char *str, char c);
char				*ft_strndup(const char *s, int n, int for_free);
char				**ft_str_split(char *s, char *c);
char				**ft_strsplit(char const *s, char c);
char				**ft_strsplit_token(char *s, char *c);
char				*ft_strtrim(char const *s);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_itoa(int n);
char				*ft_strsub(char const *s, unsigned int start, size_t len);
char				*ft_strnew(size_t size);
char				*ft_strmap(char const *s, char (*f)(char));
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char				*ft_strchr(const char *s, int c);
char				*ft_strrchr(const char *s, int c);
char				*ft_strdup(char *s1);
char				*ft_strcpy(char *dst, const char *src);
char				*ft_strncpy(char *dst, const char *src, size_t len);
char				*ft_strcat(char *s1, const char *s2);
char				*ft_strncat(char *s1, const char *s2, size_t n);
char				*ft_strstr(const char *haystack, const char *needle);
char				*ft_l_b(long long n, int base);
char				*ft_strnstr(const char *haystack,
			const char *needle, size_t len);
char				**ft_strsplit_charset(char *s, char *c);
int					read_stdin(char **line);
char				*remove_quotes(char *str);
void				remove_quotes_args(char **tab);

#endif
