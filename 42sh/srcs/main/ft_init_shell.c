#include "ft_signal.h"
#include "jobs.h"
#include "lexer.h"
#include "tree.h"
#include "env.h"
#include "exec.h"
#include "manage_line.h"
#include <term.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

static void		ft_init_tgetstr(t_shell *shell)
{
	shell->tc.dc = tgetstr("dc", 0);
	shell->tc.ce = tgetstr("ce", 0);
	shell->tc.cm = tgetstr("cm", 0);
	shell->tc.le = tgetstr("le", 0);
	shell->tc.nd = tgetstr("nd", 0);
	shell->tc.me = tgetstr("me", 0);
	shell->tc.le_m = tgetstr("LE", 0);
	shell->tc.ri_m = tgetstr("RI", 0);
	shell->tc.co = tgetnum("co");
}

void			ft_init_termcap(t_shell *shell)
{
	if (tcgetattr(0, &shell->tc.tios) == -1)
	{
		ft_putendl("error recup termcap");
		exit(1);
	}
	shell->tc.tios.c_lflag &= ~(ICANON | ECHO | ISIG);
	shell->tc.tios.c_cc[VMIN] = 1;
	shell->tc.tios.c_cc[VTIME] = 0;
	if (tcsetattr(0, 0, &shell->tc.tios) == -1)
	{
		ft_putendl("error modif termcap");
		exit(1);
	}
}

void			ft_restore_termcap(t_termcap *tc)
{
	tc->tios.c_lflag |= (ICANON | ECHO | ISIG);
	if (tcsetattr(0, 0, &tc->tios) == -1)
		printf("tcsetattr\n");
}

static	void	ft_init_shell2(t_shell *shell)
{
	shell->init.first = 0;
	shell->buf_mem = NULL;
	shell->tab_session = NULL;
	shell->tab_history = NULL;
	shell->operators = ft_strsplit(OPERATORS, ':');
	shell->line = 1;
	shell->type_term = getenv("TERM");
	if (tgetent(0, shell->type_term) == ERR)
	{
		shell->type_term = getenv("vt100");
		if (tgetent(0, shell->type_term) == ERR)
		{
			ft_putendl_fd("Probleme d'environnement", 2);
			exit(-1);
		}
	}
}

void			ft_init_shell(t_shell *shell, char **env)
{
	shell->init.evp = ft_copy_evp(env);
	ft_init_shell2(shell);
	ft_init_tgetstr(shell);
	if (!shell->tc.dc || !shell->tc.ce || !shell->tc.cm ||
			!shell->tc.le || !shell->tc.nd || !shell->tc.me || !shell->tc.co ||
				!shell->tc.le_m || !shell->tc.ri_m)
	{
		ft_putendl_fd("error termcap", 2);
		exit(1);
	}
}
