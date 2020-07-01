#include "ft_printf.h"

int		ft_return_printf2(const char *format, va_list ap, t_var *var)
{
	if (ft_printf2(format, ap, var) == -1)
	{
		ft_free(var);
		return (-1);
	}
	return (0);
}
