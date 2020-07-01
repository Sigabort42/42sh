#include "ft_printf.h"

int		ft_stock_plus(t_var *var, t_flags *s_flags, char *str_hexa)
{
	if (str_hexa[0] != '-' && s_flags->c & (1 << 1) && var->type <= TYPE_INT)
	{
		var->buf_tmp[var->i_buf_tmp++] = '+';
		return (1);
	}
	return (0);
}
