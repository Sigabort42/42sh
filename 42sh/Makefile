NAME				=	42sh

CFLAGS				=	-Wall -Wextra -Werror #-g3 -fsanitize=address

INCLUDE_LIBFT		=	../libft/
INCLUDE_21SH		=	./includes/

SRC_SIGNAL_FILE		=	ft_signal.c\
						ft_signal2.c

SRC_SIGNAL_PATH		=	./srcs/signal/

SRC_JOBS_FILE		=	ft_utils.c
SRC_JOBS_PATH		=	./srcs/jobs/

SRC_BUILTIN_FILE	=	ft_builtin_cd_utils.c\
						ft_builtin_cd.c\
						ft_builtin_echo.c\
						ft_builtin_env.c\
						ft_builtin_exit.c\
						ft_builtin_parser.c\
						ft_builtin_setenv.c\
						ft_builtin_unsetenv.c\
						ft_builtin_history.c\
						ft_builtin_history2.c\
						ft_builtin_history3.c\
						ft_builtin_history_usage.c

SRC_BUILTIN_PATH	=	./srcs/builtin/

SRC_ENV_FILE		=	ft_env_copy.c\
						ft_env_utils.c\
						ft_env.c
SRC_ENV_PATH		=	./srcs/env/

SRC_ERROR_FILE		=	ft_error.c\
						ft_builtin_error.c
SRC_ERROR_PATH		=	./srcs/error/

SRC_EXEC_FILE		=	ft_args.c\
						ft_builtin.c\
						ft_check_fd.c\
						ft_check_file.c\
						ft_command.c\
						ft_construct_tree.c\
						ft_eval_tree.c\
						ft_exec.c\
						ft_fork.c\
						ft_program.c\
						ft_tree.c
SRC_EXEC_PATH		=	./srcs/exec/

SRC_LEXER_FILE		=	ft_fusion_token_utils.c\
						ft_fusion_token.c\
						ft_lexer_debug.c\
						ft_lexer_utils.c\
						ft_lexer.c\
						ft_manage_aggregator.c\
						ft_parser.c\
						ft_redir.c\
						ft_token.c
SRC_LEXER_PATH		=	./srcs/lexer/

SRC_MAIN_FILE		=	ft_init_history.c\
						ft_init_shell.c\
						main.c
SRC_MAIN_PATH		=	./srcs/main/

SRC_MANAGELINE_FILE	=	ft_manage_line.c\
						ft_manage_line2.c\
						ft_manage_line3.c\
						ft_manage_line4.c\
						ft_verif_line.c\
						ft_manage_bang.c\
						ft_manage_bang2.c\
						ft_utils.c\
						ft_utils2.c\
						ft_check_quote.c\
						ft_check_quote2.c\
						ft_check_heredocs.c\
						ft_check_heredocs2.c

SRC_MANAGELINE_PATH	=	./srcs/manage_line/

SRC_COMPLETION_FILE	=	ft_completion.c\
						ft_find_file.c\
						ft_find_cmd.c\
						ft_list_util.c\
						ft_util.c\
						ft_case_opti.c\
						ft_print_lst.c\
						ft_return.c\

SRC_COMPLETION_PATH	=	./srcs/completion/

SRC_PARS_FILE		=	ft_pars.c\

SRC_PARS_PATH		=	./srcs/pars/

SRC_SIGNAL			= $(addprefix $(SRC_SIGNAL_PATH),$(SRC_SIGNAL_FILE))
SRC_JOBS			= $(addprefix $(SRC_JOBS_PATH),$(SRC_JOBS_FILE))
SRC_BUILTIN			= $(addprefix $(SRC_BUILTIN_PATH),$(SRC_BUILTIN_FILE))
SRC_ENV				= $(addprefix $(SRC_ENV_PATH),$(SRC_ENV_FILE))
SRC_ERROR			= $(addprefix $(SRC_ERROR_PATH),$(SRC_ERROR_FILE))
SRC_EXEC			= $(addprefix $(SRC_EXEC_PATH),$(SRC_EXEC_FILE))
SRC_LEXER			= $(addprefix $(SRC_LEXER_PATH),$(SRC_LEXER_FILE))
SRC_MAIN			= $(addprefix $(SRC_MAIN_PATH),$(SRC_MAIN_FILE))
SRC_MANAGELINE		= $(addprefix $(SRC_MANAGELINE_PATH),$(SRC_MANAGELINE_FILE))
SRC_COMPLETION		= $(addprefix $(SRC_COMPLETION_PATH),$(SRC_COMPLETION_FILE))
#SRC_PARS			= $(addprefix $(SRC_PARS_PATH),$(SRC_PARS_FILE))

SRC = $(SRC_SIGNAL)
SRC += $(SRC_JOBS)
SRC += $(SRC_BUILTIN)
SRC += $(SRC_ERROR)
SRC += $(SRC_EXEC)
SRC += $(SRC_LEXER)
SRC += $(SRC_MANAGELINE)
SRC += $(SRC_COMPLETION)
#SRC += $(SRC_PARS)
SRC += $(SRC_MAIN)
SRC += $(SRC_ENV)
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@make -C ../libft
	@clang $(CFLAGS) $(OBJ) -o $(NAME) -L../libft -lft -ltermcap

%.o : %.c
	@clang $(CFLAGS) -I $(INCLUDE_LIBFT) -I $(INCLUDE_21SH) -c $< -o $@

clean:
	@/bin/rm -rf $(OBJ)
	@make -C ../libft clean

fclean: clean
	@/bin/rm -rf $(NAME)
	@make -C ../libft fclean

re: fclean all
