#include "rush02.h"

static void	dr_copy_bytes(char *dst, const char *src, int n)
{
	int i;

	i = 0;
	while (i < n)
	{
		dst[i] = src[i];
		i++;
	}
}

static int	dr_expand(char **buf, int *cap, int need, int len)
{
	char	*newb;
	int	 newcap;

	if (need <= *cap)
		return (1);
	newcap = *cap * 2;
	if (newcap < need)
		newcap = need;
	newb = (char *)malloc(newcap);
	if (!newb)
		return (0);
	dr_copy_bytes(newb, *buf, len);
	free(*buf);
	*buf = newb;
	*cap = newcap;
	return (1);
}

int		dr_process_buffer(t_dict *d, char *buf, int len)
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
			line = dl_substr_dup(buf, start, i - 1);
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
		line = dl_substr_dup(buf, start, len - 1);
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

int		dr_read_all(int fd, char **out_buf, int *out_len)
{
	char	*buf;
	int	 cap;
	int	 len;
	char	*tmp;
	int	 n;

	cap = READ_BUF_SIZE;
	len = 0;
	buf = (char *)malloc(cap);
	if (!buf)
		return (0);
	tmp = (char *)malloc(READ_BUF_SIZE);
	if (!tmp)
		return (free(buf), 0);
	n = read(fd, tmp, READ_BUF_SIZE);
	while (n > 0)
	{
		if (!dr_expand(&buf, &cap, len + n + 1, len))
			return (free(tmp), free(buf), 0);
		dr_copy_bytes(buf + len, tmp, n);
		len += n;
		n = read(fd, tmp, READ_BUF_SIZE);
	}
	free(tmp);
	if (n < 0)
		return (free(buf), 0);
	buf[len] = '\0';
	*out_buf = buf;
	*out_len = len;
	return (1);
}
