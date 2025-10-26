/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dict_line_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manzo <manzo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 18:28:31 by manzo             +#+    #+#             */
/*   Updated: 2025/10/26 18:28:31 by manzo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rush02.h"

int	dl_find_colon(const char *s)
{
	int i;

	i = 0;
	while (s[i])
	{
		if (s[i] == ':')
			return (i);
		i++;
	}

int		dl_parse_line(const char *line, char **out_num, char **out_word)
{
    int	 cpos;
    char	*left;
    char	*right;
    char	*num;
    char	*word;

    cpos = dl_find_colon(line);
    if (cpos < 0)
        return (2);
    left = dl_substr_dup(line, 0, cpos - 1);
    right = dl_substr_dup(line, cpos + 1, ft_strlen(line) - 1);
    if (!left || !right)
    {
        free(left);
        free(right);
        return (0);
    }
    num = dl_extract_number(left);
    free(left);
    if (!num)
        return (free(right), 0);
    word = str_trim_spaces(right);
    free(right);
    if (!word)
        return (free(num), 0);
    *out_num = num;
    *out_word = word;
    return (1);
	return (-1);
}

char	*dl_substr_dup(const char *s, int start, int end)
{
	int		len;
	char	*out;
	int		i;

	if (end < start)
		return (ft_strdup(""));
	len = end - start + 1;
	out = (char *)malloc(len + 1);
	if (!out)
		return (0);
	i = 0;
	while (i < len)
	{
		out[i] = s[start + i];
		i++;
	}
	out[i] = '\0';
	return (out);
}

static int	find_arrow(const char *s)
{
	int i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '\xE2' && s[i + 1] && s[i + 2])
			return (i);
		if (s[i] == '-' && s[i + 1] == '>')
			return (i);
		if (s[i] == '>')
			return (i);
		i++;
	}
	return (-1);
}

char	*dl_extract_number(const char *left)
{
	int	 apos;
	char	*tmp;
	char	*sp;
	int	 i;
	int	 j;
	char	*out;

	apos = find_arrow(left);
	if (apos >= 0)
		tmp = dl_substr_dup(left, apos + 1, ft_strlen(left) - 1);
	else
		tmp = ft_strdup(left);
	if (!tmp)
		return (0);
	sp = str_trim_spaces(tmp);
	free(tmp);
	if (!sp)
		return (0);
	out = (char *)malloc(ft_strlen(sp) + 1);
	if (!out)
	{
		free(sp);
		return (0);
	}
	i = 0;
	j = 0;
	while (sp[i])
	{
		if (sp[i] >= '0' && sp[i] <= '9')
			out[j++] = sp[i];
		i++;
	}
	out[j] = '\0';
	free(sp);
	return (out);
}
