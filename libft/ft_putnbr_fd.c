#include "libft.h"

static void	ft_appelle_fd(int nb, int fd)
{
	if (nb < 10)
	{
		ft_putchar_fd(nb + 48, fd);
	}
	else
	{
		ft_appelle_fd(nb / 10, fd);
		ft_putchar_fd((nb % 10) + 48, fd);
	}
}

void		ft_putnbr_fd(int nb, int fd)
{
	if (nb < 0)
	{
		ft_putchar_fd('-', fd);
		if (nb == -2147483648)
		{
			ft_appelle_fd(214748364, fd);
			ft_putchar_fd('8', fd);
		}
		else
			ft_appelle_fd(-nb, fd);
	}
	else
	{
		ft_appelle_fd(nb, fd);
	}
}
