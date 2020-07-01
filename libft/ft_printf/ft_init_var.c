#include "ft_printf.h"

void	ft_init_var(t_var *var)
{
	var->buf = (char *)malloc(sizeof(char) * 10000);
	var->buf_tmp = (char *)malloc(sizeof(char) * 10000);
	var->ret = 0;
	var->i_buf = 0;
	var->nb_conv = 0;
	ft_strcpy(var->flags_conv, "cCdDioOuUxXpsSb");
}

int		ft_verif_wchar_nb(t_var *var)
{
	if (var->type == TYPE_WCHAR && !var->nb_conv)
	{
		free(var->buf);
		free(var->buf_tmp);
		return (-1);
	}
	return (0);
}
