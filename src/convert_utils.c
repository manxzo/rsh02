#include "rush02.h"

static void	build_small_key(int n, char *key)
{
	if (n < 10)
	{
		key[0] = '0' + n;
		key[1] = '\0';
	}
	else if (n < 20)
	{
		key[0] = '1';
		key[1] = '0' + (n - 10);
		key[2] = '\0';
	}
	else if (n < 100)
	{
		key[0] = '0' + (n / 10);
		key[1] = '0';
		key[2] = '\0';
	}
	else
	{
		key[0] = '1';
		key[1] = '0';
		key[2] = '0';
		key[3] = '\0';
	}
}

static int	print_key_word(const t_dict *d, int n, t_print *p)
{
	char		key[12];
	const char	*w;

	build_small_key(n, key);
	w = dict_find(d, key);
	if (!w)
		return (0);
	print_word(p, w);
	return (1);
}

static int	print_below_100(const t_dict *d, int n, t_print *p)
{
	int						t;
	int						u;
	const char				*w;
	char					 key[12];

	if (n == 0)
		return (1);
	if (n <= 19)
		return (print_key_word(d, n, p));
	t = (n / 10) * 10;
	u = n % 10;
	build_small_key(t, key);
	w = dict_find(d, key);
	if (!w)
		return (0);
	print_word(p, w);
	if (u > 0)
	{
		build_small_key(u, key);
		w = dict_find(d, key);
		if (!w)
			return (0);
		ft_putchar('-');
		ft_putstr(w);
	}
	return (1);
}

int		print_triad_words(const t_dict *d, int triad, t_print *p)
{
	int	 h;
	int	 r;

	h = triad / 100;
	r = triad % 100;
	if (h > 0)
	{
		if (!print_key_word(d, h, p))
			return (0);
		if (!print_key_word(d, 100, p))
			return (0);
	}
	if (r > 0)
	{
		if (h > 0)
			print_word(p, "and");
		if (!print_below_100(d, r, p))
			return (0);
	}
	return (1);
}

int		print_scale_word(const t_dict *d, int groups_left, t_print *pr)
{
	char	*key;
	int	 needed;
	int	 i;
	const char	*w;

	needed = 3 * groups_left + 2;
	key = (char *)malloc(needed);
	if (!key)
		return (0);
	key[0] = '1';
	i = 1;
	while (i < needed - 1)
		key[i++] = '0';
	key[i] = '\0';
	w = dict_find(d, key);
	free(key);
	if (!w)
		return (0);
	print_word(pr, w);
	return (1);
}
