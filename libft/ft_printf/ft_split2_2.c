#include "ft_printf.h"

void	ft_split2_2(t_flags *s_flags, t_var *var, char *str_hexa)
{
	ft_stock_plus(var, s_flags, str_hexa);
	ft_stock_buf_base(var, s_flags, var->res_strcmp);
	var->k = s_flags->precision - var->len_str_hexa + var->i_moins;
	ft_memset(&var->buf_tmp[var->i_buf_tmp], '0', var->k);
	var->i_buf_tmp += var->k;
	ft_memcpy(&var->buf_tmp[var->i_buf_tmp], &str_hexa[var->i_moins],
			var->len_str_hexa);
}
