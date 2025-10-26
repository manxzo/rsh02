/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manzo <manzo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 17:03:08 by manzo             +#+    #+#             */
/*   Updated: 2025/10/26 17:03:51 by manzo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rush02.h"

static int	int_to_str(int n, char *buf)
{
	int	len;
	int	d;
	int	i;
	char	tmp[12];

	if (n == 0)
	{
		buf[0] = '0';
		buf[1] = '\0';
		return (1);
	}
	len = 0;
	while (n > 0)
	{
		d = n % 10;
		tmp[len] = (char)('0' + d);
		len++;
		n /= 10;
	}
	i = 0;
	while (i < len)
	{
		buf[i] = tmp[len - 1 - i];
		i++;
	}
	buf[len] = '\0';
	return (len);
}

static int	print_key_word(const t_dict *d, int n, t_print *p)
{
	char	key[12];
	const char	*w;

	int_to_str(n, key);
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
	int_to_str(t, key);
	w = dict_find(d, key);
	if (!w)
		return (0);
	print_word(p, w);
	if (u > 0)
	{
		int_to_str(u, key);
		w = dict_find(d, key);
		if (!w)
			return (0);
		ft_putchar('-');
		ft_putstr(w);
	}
	return (1);
}

static int	print_triad_words(const t_dict *d, int triad, t_print *p)
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

int		print_number_words(const t_dict *d, const char *num_str)
{
	int		len;
	int		groups;
	int		first_len;
	int		i;
	int		triad;
	int		start;
	int		pos;
	int		j;
	int		has_more;
	char	*scale_key;
	const char	*w;
	t_print	pr;

	if (!num_str || !d)
		return (0);
	if (ft_strcmp(num_str, "0") == 0)
	{
		w = dict_find(d, "0");
		if (!w)
			return (0);
		ft_putstr(w);
		return (1);
	}
	pr.first = 1;
	len = ft_strlen(num_str);
	groups = len / 3;
	first_len = len % 3;
	if (first_len == 0)
	{
		first_len = 3;
		groups -= 1;
	}
	i = 0;
	pos = 0;
	while (i <= groups)
	{
		if (i == 0)
			start = 0;
		else
			start = pos;
		if (i == 0)
			triad = 0;
		if (i == 0)
		{
			triad = 0;
			while (pos < first_len)
			{
				triad = triad * 10 + (num_str[pos] - '0');
				pos++;
			}
		}
		else
		{
			triad = (num_str[pos] - '0') * 100 + (num_str[pos + 1] - '0') * 10
				+ (num_str[pos + 2] - '0');
			pos += 3;
		}
		if (triad > 0)
		{
			if (!print_triad_words(d, triad, &pr))
				return (0);
			if (groups - i > 0)
			{
				scale_key = (char *)malloc(3 * (groups - i) + 2);
				if (!scale_key)
					return (0);
				scale_key[0] = '1';
				start = 1;
				while (start < 3 * (groups - i) + 1)
				{
					scale_key[start] = '0';
					start++;
				}
				scale_key[start] = '\0';
				w = dict_find(d, scale_key);
				free(scale_key);
				if (!w)
					return (0);
				print_word(&pr, w);
				j = pos;
				has_more = 0;
				while (j < len)
				{
					if (num_str[j] != '0')
					{
						has_more = 1;
						break;
					}
					j++;
				}
				if (has_more)
				{
					ft_putchar(',');
					ft_putchar(' ');
					pr.first = 1;
				}
			}
		}
		i++;
	}
	return (1);
}
