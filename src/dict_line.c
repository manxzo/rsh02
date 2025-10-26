#include "rush02.h"

static char	*substr_dup(const char *s, int start, int end)
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

static int	find_colon(const char *s)
{
	int i;

	i = 0;
	while (s[i])
	{
		if (s[i] == ':')
			return (i);
		i++;
	}
	return (-1);
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

static char	*trim_digits(const char *s)
{
	char	*tmp;
	char	*out;
	int		i;
	int		j;

	tmp = str_trim_spaces(s);
	if (!tmp)
		return (0);
	i = 0;
	j = 0;
	out = (char *)malloc(ft_strlen(tmp) + 1);
	if (!out)
	{
		free(tmp);
		return (0);
	}
	while (tmp[i])
	{
		if (tmp[i] >= '0' && tmp[i] <= '9')
			out[j++] = tmp[i];
		i++;
	}
	out[j] = '\0';
	free(tmp);
	return (out);
}

int		dict_process_line(t_dict *d, const char *line)
{
	int		cpos;
	int		apos;
	char	*left;
	char	*right;
	char	*num0;
	char	*num;
	char	*word;
	char	*t;

	cpos = find_colon(line);
	if (cpos < 0)
		return (1);
	left = substr_dup(line, 0, cpos - 1);
	right = substr_dup(line, cpos + 1, ft_strlen(line) - 1);
	if (!left || !right)
	{
		free(left);
		free(right);
		return (0);
	}
	apos = find_arrow(left);
	if (apos >= 0)
		num0 = substr_dup(left, apos + 1, ft_strlen(left) - 1);
	else
		num0 = ft_strdup(left);
	free(left);
	if (!num0)
	{
		free(right);
		return (0);
	}
	t = trim_digits(num0);
	free(num0);
	num = t;
	if (!num)
	{
		free(right);
		return (0);
	}
	word = str_trim_spaces(right);
	free(right);
	if (!word)
	{
		free(num);
		return (0);
	}
	if (num[0] == '\0' || word[0] == '\0')
	{
		free(num);
		free(word);
		return (1);
	}
	if (!dict_add(d, num, word))
	{
		free(num);
		free(word);
		return (1);
	}
	free(num);
	free(word);
	return (1);
}
