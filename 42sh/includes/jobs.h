#ifndef JOBS_H
# define JOBS_H
# include "exec.h"

void		init_shell_jobs();
t_job		*find_job(pid_t pgid);
int			job_is_stopped(t_job *j);
int			job_is_completed(t_job *j);

#endif
