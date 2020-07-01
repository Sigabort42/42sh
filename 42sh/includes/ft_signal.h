#ifndef FT_SIGNAL_H
# define FT_SIGNAL_H

# include "../../libft/libft.h"

char	**g_signal;

void	ft_init_signal(void);
void	ft_print_signal_child(int sig, int pid);
void	ft_sigabrt(int sig);
void	ft_sigsegv(int sig);
void	ft_sigkill(int sig);
void	ft_sigterm(int sig);
void	ft_sighup(int sig);
void	ft_sigquit(int sig);
void	ft_sigintr(int sig);
void	ft_sigbuserr(int sig);

#endif
