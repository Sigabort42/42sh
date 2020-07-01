#include <signal.h>
#include <sys/types.h>
#include <termios.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "jobs.h"
#include "exec.h"

void		init_shell_jobs(t_shell *shell)
{
	shell->shell_terminal = STDIN_FILENO;
	shell->shell_is_interactive = isatty(shell->shell_terminal);
	if (shell->shell_is_interactive)
	{
		while (tcgetpgrp(shell->shell_terminal) !=
				(shell->shell_pgid = getpgrp()))
			kill(shell->shell_pgid, SIGTTIN);
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		signal(SIGTSTP, SIG_IGN);
		signal(SIGTTIN, SIG_IGN);
		signal(SIGTTOU, SIG_IGN);
		signal(SIGCHLD, SIG_IGN);
		shell->shell_pgid = getpid();
		if (setpgid(shell->shell_pgid, shell->shell_pgid) < 0)
		{
			perror("Can't place shell in his group process");
			exit(1);
		}
		tcsetpgrp(shell->shell_terminal, shell->shell_pgid);
		tcgetattr(shell->shell_terminal, &(shell)->tc.shell_tmodes);
	}
}

t_job		*find_job(pid_t pgid)
{
	t_job		*j;

	j = g_first_job;
	while (j)
	{
		if (j->pgid == pgid)
			return (j);
		j = j->next;
	}
	return (0);
}

int			job_is_stopped(t_job *j)
{
	t_process	*p;

	p = j->first_process;
	while (p)
	{
		if (!p->completed && !p->stopped)
			return (0);
		p = p->next;
	}
	return (1);
}

int			job_is_completed(t_job *j)
{
	t_process	*p;

	p = j->first_process;
	while (p)
	{
		if (!p->completed)
			return (0);
		p = p->next;
	}
	return (1);
}
