#include "rush02.h"

int	ft_is_space(char c)
{
	if (c == ' ')
		return (1);
	if (c == '\t')
		return (1);
	if (c == '\n')
		return (1);
	if (c == '\v')
		return (1);
	if (c == '\f')
		return (1);
	if (c == '\r')
		return (1);
	return (0);
}

int	ft_str_is_numeric(const char *s)
{
	int i;

	i = 0;
	if (!s || !s[0])
		return (0);
	while (s[i])
	{
		if (s[i] < '0' || s[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

char	*ft_strdup(const char *s)
{
	int		len;
	char	*out;
	int		i;

	len = ft_strlen(s);
	out = (char *)malloc(len + 1);
	if (!out)
		return (0);
	i = 0;
	while (i < len)
	{
		out[i] = s[i];
		i++;
	}
	out[i] = '\0';
	return (out);
}

static int	left_trim_index(const char *s)
{
	int i;

	i = 0;
	while (s[i] && ft_is_space(s[i]))
		i++;
	return (i);
}

char	*str_trim_spaces(const char *s)
{
	int	l;
	int	r;
	char	*out;
	int	i;

	l = left_trim_index(s);
	r = ft_strlen(s) - 1;
	while (r >= l && ft_is_space(s[r]))
		r--;
	if (r < l)
		return (ft_strdup(""));
	out = (char *)malloc(r - l + 2);
	if (!out)
		return (0);
	i = 0;
	while (l <= r)
	{
		out[i] = s[l];
		i++;
		l++;
	}
	out[i] = '\0';
	return (out);
}
