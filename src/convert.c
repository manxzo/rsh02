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

static int	process_groups(const t_dict *d, const char *s, int first_len, int groups)
{
    int	 len;
    int	 i;
    int	 pos;
    int	 triad;
    t_print pr;

    pr.first = 1;
    len = ft_strlen(s);
    i = 0;
    pos = 0;
    while (i <= groups)
    {
        if (i == 0)
            triad = cr_read_first_triad(s, first_len, &pos);
        else
            triad = cr_read_next_triad(s, &pos);
        if (triad > 0)
        {
            if (!print_triad_words(d, triad, &pr))
                return (0);
            if (groups - i > 0)
            {
                if (!print_scale_word(d, groups - i, &pr))
                    return (0);
                if (cr_has_more_nonzero(s, pos, len))
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

int		print_number_words(const t_dict *d, const char *num_str)
{
    int		len;
    int		groups;
    int		first_len;
    const char	*w;

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
    len = ft_strlen(num_str);
    groups = len / 3;
    first_len = len % 3;
    if (first_len == 0)
    {
        first_len = 3;
        groups -= 1;
    }
    return (process_groups(d, num_str, first_len, groups));
}
