#include "rush02.h"

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putstr(const char *s)
{
	if (!s)
		return;
	write(1, s, ft_strlen(s));
}

void	ft_puterr(const char *s)
{
	if (!s)
		return;
	write(2, s, ft_strlen(s));
}

void	print_word(t_print *p, const char *w)
{
	if (!w)
		return;
	if (!p->first)
		ft_putchar(' ');
	else
		p->first = 0;
	ft_putstr(w);
}
