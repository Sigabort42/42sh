#include "ft_signal.h"
#include "manage_line.h"
#include "env.h"
#include <signal.h>

void	ft_sigtstp(int sig)
{
	(void)sig;
}

void	ft_sigwinch(int sig)
{
	(void)sig;
}

void	ft_init_signal2(void)
{
	g_signal[18] = ft_strdup("");
	g_signal[19] = ft_strdup("child status has changed");
	g_signal[20] = ft_strdup("background read attempted from control terminal");
	g_signal[21] = ft_strdup("background write attempted to control terminal");
	g_signal[22] = ft_strdup("I/O is possible on a descriptor (see fcntl(2))");
	g_signal[23] = ft_strdup("cpu time limit exceeded (see setrlimit(2))");
	g_signal[24] = ft_strdup("file size limit exceeded (see setrlimit(2))");
	g_signal[25] = ft_strdup("virtual time alarm (see setitimer(2))");
	g_signal[26] = ft_strdup("profiling timer alarm (see setitimer(2))");
	g_signal[27] = ft_strdup("Window size change");
	g_signal[28] = ft_strdup("status request from keyboard");
	g_signal[29] = ft_strdup("User defined signal 1");
	g_signal[30] = ft_strdup("User defined signal 2");
	g_signal[31] = NULL;
	signal(SIGINT, &ft_sigintr);
	signal(SIGTSTP, &ft_sigtstp);
	signal(SIGWINCH, &ft_sigwinch);
}

void	ft_init_signal(void)
{
	g_signal = malloc(sizeof(char*) * 32);
	g_signal[0] = ft_strdup("terminal line hangup");
	g_signal[1] = ft_strdup("interrupt program");
	g_signal[2] = ft_strdup("quit program");
	g_signal[3] = ft_strdup("illegal instruction");
	g_signal[4] = ft_strdup("trace trap");
	g_signal[5] = ft_strdup("abort program");
	g_signal[6] = ft_strdup("emulate instruction executed");
	g_signal[7] = ft_strdup("floating-point exception");
	g_signal[8] = ft_strdup("kill program");
	g_signal[9] = ft_strdup("bus error");
	g_signal[10] = ft_strdup("Segmentation fault");
	g_signal[11] = ft_strdup("Segmentation fault");
	g_signal[12] = ft_strdup("SIGPIPE");
	g_signal[13] = ft_strdup("real-time timer expired");
	g_signal[14] = ft_strdup("software termination signal");
	g_signal[15] = ft_strdup("urgent condition present on socket");
	g_signal[16] = ft_strdup("stop (cannot be caught or ignored)");
	g_signal[17] = ft_strdup("stop signal generated from keyboard");
	ft_init_signal2();
}

void	ft_print_signal_child(int sig, int pid)
{
	if (sig != SIGQUIT && sig != 7 && sig < 13)
	{
		ft_putstr("[1]");
		ft_putnbr(pid);
		ft_putstr(" ");
		ft_putnbr(sig - 1);
		ft_putendl(g_signal[sig - 1]);
	}
}
