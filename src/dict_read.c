#include "rush02.h"

static void	copy_bytes(char *dst, const char *src, int n)
{
	int i;

	i = 0;
	while (i < n)
	{
		dst[i] = src[i];
		i++;
	}
}

static char	*substr_dup2(const char *s, int start, int end)
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

static int	process_buffer(t_dict *d, char *buf, int len)
{
	int	 start;
	int	 i;
	char	*line;

	start = 0;
	i = 0;
	while (i < len)
	{
		if (buf[i] == '\n' || buf[i] == '\r')
		{
			line = substr_dup2(buf, start, i - 1);
			if (!line)
				return (0);
			if (!dict_process_line(d, line))
			{
				free(line);
				return (0);
			}
			free(line);
			start = i + 1;
		}
		i++;
	}
	if (start < len)
	{
		line = substr_dup2(buf, start, len - 1);
		if (!line)
			return (0);
		if (!dict_process_line(d, line))
		{
			free(line);
			return (0);
		}
		free(line);
	}
	return (1);
}

static int	read_all(int fd, char **out_buf, int *out_len)
{
	char	*buf;
	int	 cap;
	int	 len;
	char	*tmp;
	int	 n;
	char	*newb;
	int	 need;

	cap = READ_BUF_SIZE;
	len = 0;
	buf = (char *)malloc(cap);
	if (!buf)
		return (0);
	tmp = (char *)malloc(READ_BUF_SIZE);
	if (!tmp)
	{
		free(buf);
		return (0);
	}
	n = read(fd, tmp, READ_BUF_SIZE);
	while (n > 0)
	{
		need = len + n + 1;
		if (need > cap)
		{
			newb = (char *)malloc(need * 2);
			if (!newb)
			{
				free(tmp);
				free(buf);
				return (0);
			}
			copy_bytes(newb, buf, len);
			free(buf);
			buf = newb;
			cap = need * 2;
		}
		copy_bytes(buf + len, tmp, n);
		len += n;
		n = read(fd, tmp, READ_BUF_SIZE);
	}
	free(tmp);
	if (n < 0)
	{
		free(buf);
		return (0);
	}
	buf[len] = '\0';
	*out_buf = buf;
	*out_len = len;
	return (1);
}

int		load_dictionary(const char *path, t_dict *d)
{
	int	 fd;
	char	*buf;
	int	 len;
	int	 ok;

	dict_init(d);
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (0);
	buf = 0;
	len = 0;
	ok = read_all(fd, &buf, &len);
	close(fd);
	if (!ok)
		return (0);
	ok = process_buffer(d, buf, len);
	free(buf);
	return (ok);
}
