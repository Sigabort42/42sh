#include "ft_printf.h"

int	ft_verif_address(t_var *var)
{
	if (var->type == TYPE_ADDRESS)
	{
		ft_memcpy(&var->buf[var->i_buf], var->buf_tmp, var->i_buf_tmp);
		var->i_buf += var->i_buf_tmp;
		return (1);
	}
	return (0);
}
