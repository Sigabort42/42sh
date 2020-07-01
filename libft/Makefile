# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jtaibi <jtaibi@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/08 17:04:50 by elbenkri          #+#    #+#              #
#    Updated: 2018/11/19 15:39:43 by jtaibi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	libft.a

NAME_TMP		=	tmp_libft.a

CC				=	gcc

CFLAGS			=	-Wall -Wextra -Werror #-g3 -fsanitize=address

SRCS			=	ft_strlen.c \
				ft_intlen.c\
				ft_tablen.c \
				ft_count_char.c \
				ft_index.c \
				ft_strcmp.c \
				ft_strncmp.c \
				ft_isalpha.c \
				ft_isalnum.c \
				ft_isdigit.c \
				ft_isascii.c \
				ft_isprint.c \
				ft_strdup.c \
				ft_toupper.c \
				ft_tolower.c \
				ft_strcpy.c \
				ft_strncpy.c \
				ft_strcat.c \
				ft_strncat.c \
				ft_strlcat.c \
				ft_strstr.c \
				ft_strnstr.c \
				ft_strchr.c \
				ft_strrchr.c \
				ft_atoi.c \
				ft_strnew.c \
				ft_strclr.c \
				ft_strdel.c \
				ft_striter.c \
				ft_striteri.c \
				ft_strmap.c \
				ft_strmapi.c \
				ft_strequ.c \
				ft_strnequ.c \
				ft_putstr.c \
				ft_putchar.c \
				ft_putendl.c \
				ft_putnbr.c \
				ft_putnbr_fd.c \
				ft_putendl_fd.c \
				ft_putstr_fd.c \
				ft_putchar_fd.c \
				ft_strsub.c \
				ft_memset.c \
				ft_bzero.c \
				ft_memcpy.c \
				ft_memccpy.c \
				ft_memcmp.c \
				ft_memchr.c \
				ft_memmove.c \
				ft_memalloc.c \
				ft_memdel.c \
				ft_strsplit.c \
				ft_strtrim.c \
				ft_strjoin.c \
				ft_itoa.c \
				ft_lstnew.c \
				ft_lstadd.c \
				ft_lstdel.c \
				ft_lstdelone.c \
				ft_lstiter.c \
				ft_lstmap.c \
				ft_lstcount.c \
				ft_isupper.c \
				ft_islower.c \
				ft_lstpushback.c \
				ft_strrev.c \
				ft_lstlast.c \
				ft_lstpushparams.c \
				ft_strcdup.c \
				ft_strjoin_free.c \
				get_next_line.c \
				ft_split.c \
				ft_strndup.c \
				ft_btree.c \
				ft_btree_add_node.c \
				ft_recursive_power.c \
				ft_l_b.c \
				ft_str_split.c \
				ft_str_isdigit.c \
				ft_strsplit_charset.c \
				ft_concat_tab.c \
				ft_isspace.c \
				ft_strstart.c \
				ft_issign.c \
				ft_getword.c \
				read_stdin.c \
				ft_isspace_word.c \
				ft_strcut.c \
				ft_strpush.c\
				ft_strsplit_token.c\
				ft_quotes.c

OBJ			=	$(SRCS:.c=.o)

HEADER			=	libft.h

all: $(NAME)

$(NAME): $(OBJ)
	@ar rc $(NAME_TMP) $(OBJ)
	@make -C ft_printf/
	@libtool -static -o $(NAME) $(NAME_TMP) ft_printf/printf.a
	@ranlib	$(NAME)
	@rm -rf $(NAME_TMP)
	@echo "\033[32mLibft [\033[32;5mOk\033[0m\033[32m]"

clean:
	@make -C ft_printf/ clean
	@rm -rf $(OBJ)
	@echo "\033[32mLibft.o [\033[32;5mCleaned\033[0m\033[32m]"

fclean:	clean
	@make -C ft_printf/ fclean
	@rm -rf $(NAME)
	@echo "\033[32mLibft [\033[32;5mCleaned\033[0m\033[32m]"

re: fclean all
