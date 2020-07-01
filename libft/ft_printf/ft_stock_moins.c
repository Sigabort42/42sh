#include "ft_printf.h"

int		ft_stock_moins(t_var *var, char *str_hexa)
{
	if (str_hexa[0] == '-')
	{
		var->buf_tmp[var->i_buf_tmp++] = '-';
		return (1);
	}
	return (0);
}
