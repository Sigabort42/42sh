#ifndef MAIN_H
# define MAIN_H

# include "manage_line.h"

void		ft_init_history(t_shell *shell);
void		ft_init_termcap(t_shell *shell);
void		ft_restore_termcap(t_termcap *tc);
void		ft_init_shell(t_shell *shell, char **env);

#endif
