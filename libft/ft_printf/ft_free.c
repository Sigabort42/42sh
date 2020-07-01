#include "ft_printf.h"

void	ft_free(t_var *var)
{
	free(var->buf);
	free(var->buf_tmp);
}
