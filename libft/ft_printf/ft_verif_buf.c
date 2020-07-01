#include "ft_printf.h"

void	ft_verif_buf(t_var *var, const char *format)
{
	if (var->i_buf > 10000)
	{
		write(1, var->buf, 10000);
		var->i_buf = 0;
		ft_bzero(var->buf, 10000);
	}
	var->ret += ft_stock_flags(&((char*)format)[var->ret], var);
}
