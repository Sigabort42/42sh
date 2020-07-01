#include "ft_printf.h"

void	ft_split2_5(t_flags *s_flags, t_var *var)
{
	if (var->type == TYPE_ADDRESS)
		var->k = s_flags->largeur - var->len_str_hexa - 2;
	else if (s_flags->precision < var->len_str_hexa && var->res_strcmp)
		var->k = s_flags->largeur - var->len_str_hexa;
	else if ((s_flags->largeur >= s_flags->precision + var->len_str_hexa &&
		var->res_strcmp && var->type != TYPE_BITWISE) ||
		s_flags->precision >= var->len_str_hexa)
		var->k = s_flags->largeur - s_flags->precision - var->len_str_hexa;
	else
		var->k = s_flags->largeur - s_flags->precision;
}
