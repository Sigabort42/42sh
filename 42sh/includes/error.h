#ifndef ERROR_H
# define ERROR_H

/*
**		exec errors
*/
# define EXEC_BUILTIN_NOT_FOUND	-1
# define EXEC_OK				0
# define EXEC_BUILTIN_FOUND		1
# define EXEC_PATH_NO_RIGHTS	2
# define EXEC_CMD_NOT_FOUND		3
# define EXEC_BUILTIN_ECHO		4
# define EXEC_BUILTIN_CD		5
# define EXEC_BUILTIN_SETENV	6
# define EXEC_BUILTIN_UNSETENV	7
# define EXEC_BUILTIN_ENV		8
# define EXEC_BUILTIN_EXIT		9
# define EXEC_BUILTIN_HISTORY	10
# define EXEC_BAD_REDIR			11

/*
**		parsing error
*/
# define PARSER_CHK_FILE			11
# define PARSER_OP_END				12

/*
**		echo errors
*/
# define ECHO_OPT_NOT_FOUND			41

/*
**		cd errors
*/
# define CD_DIRECTORY_NOT_EXISTING	51
# define CD_HOME_NOT_SET			52
# define CD_OP_NOT_FOUND			53
# define CD_CHDIR_ERROR				54
# define CD_NOT_A_DIRECTORY			55
# define CD_PERMISSION_DENIED		56
# define CD_OLDPWD_NOT_DEFINE		57

/*
**		setenv errors
*/
# define SETENV_NAME_CONTAINS_EQUAL	61
# define SETENV_NAME_LETTER			62
# define SETENV_TOO_MANY_ARG		63
# define SETENV_VALUE_BRACKET		64

/*
**		env errors
*/
# define ENV_CMD_NOT_FOUND			81
# define ENV_OPT_NOT_FOUND			82
# define ENV_SETENV_FAIL			83
# define ENV_ADD_ENV				84
# define ENV_CMD_END				85

/*
**		exit errors
*/
# define EXIT_TOO_MANY_ARG			91

/*
**		file open errors
*/
# define FILE_NOT_FOUND				101
# define FILE_NOT_ACCESS			102
# define FILE_IS_DIR				103

/*
**		manage errors
*/
int					ft_usage_env(char ret, char *str, int flag);
int					ft_usage_setenv(int flag);
int					ft_usage_cd(int flag, char *str, int ret);
int					ft_usage_exit(int flag);
int					ft_usage_prog(int flag, char *str);
int					ft_usage_file(int flag, char *str);

#endif
