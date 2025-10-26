#include "rush02.h"

static char	*substr_dup3(const char *s, int start, int end)
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

static int	handle_line(const t_dict *d, const char *line)
{
	char	*trim;
	char	*norm;
	int		ok;

	trim = str_trim_spaces(line);
	if (!trim)
		return (0);
	if (trim[0] == '\0')
		return (free(trim), 1);
	norm = normalize_number(trim);
	free(trim);
	if (!norm)
		return (ft_puterr("Error\n"), 1);
	ok = print_number_words(d, norm);
	free(norm);
	if (!ok)
		return (ft_puterr("Dict Error\n"), 1);
	ft_putchar('\n');
	return (1);
}

int		process_stdin(const t_dict *d)
{
	char	*buf;
	int	 cap;
	int	 len;
	int	 i;
	int	 start;
	char	 tmp[READ_BUF_SIZE];
	int	 n;

	cap = READ_BUF_SIZE;
	len = 0;
	buf = (char *)malloc(cap);
	if (!buf)
		return (0);
	n = read(0, tmp, READ_BUF_SIZE);
	while (n > 0)
	{
		if (len + n + 1 > cap)
		{
			char *newb;
			int newcap;

			newcap = (len + n + 1) * 2;
			newb = (char *)malloc(newcap);
			if (!newb)
				return (free(buf), 0);
			i = 0;
			while (i < len)
			{
				newb[i] = buf[i];
				i++;
			}
			free(buf);
			buf = newb;
			cap = newcap;
		}
		i = 0;
		while (i < n)
		{
			buf[len + i] = tmp[i];
			i++;
		}
		len += n;
		start = 0;
		i = 0;
		while (i < len)
		{
			if (buf[i] == '\n')
			{
				char *line;
				line = substr_dup3(buf, start, i - 1);
				if (!line)
					return (free(buf), 0);
				handle_line(d, line);
				free(line);
				start = i + 1;
			}
			i++;
		}
		if (start > 0 && start < len)
		{
			int rest;
			rest = len - start;
			i = 0;
			while (i < rest)
			{
				buf[i] = buf[start + i];
				i++;
			}
			len = rest;
		}
		n = read(0, tmp, READ_BUF_SIZE);
	}
	if (len > 0)
	{
		char *line;
		line = substr_dup3(buf, 0, len - 1);
		if (!line)
			return (free(buf), 0);
		handle_line(d, line);
		free(line);
	}
	free(buf);
	return (1);
}
