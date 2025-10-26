#include "rush02.h"

static int	sm_expand(char **buf, int *cap, int need, int len)
{
    char	*newb;
    int	 newcap;
    int	 i;

    if (need <= *cap)
        return (1);
    newcap = *cap * 2;
    if (newcap < need)
        newcap = need;
    newb = (char *)malloc(newcap);
    if (!newb)
        return (0);
    i = 0;
    while (i < len)
    {
        newb[i] = (*buf)[i];
        i++;
    }
    free(*buf);
    *buf = newb;
    *cap = newcap;
    return (1);
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

static int	sm_process_pending(const t_dict *d, char *buf, int *len)
{
    int	 i;
    int	 start;
    char	*line;
    int	 rest;
    int	 j;

    start = 0;
    i = 0;
    while (i < *len)
    {
        if (buf[i] == '\n')
        {
            line = dl_substr_dup(buf, start, i - 1);
            if (!line)
                return (0);
            handle_line(d, line);
            free(line);
            start = i + 1;
        }
        i++;
    }
    if (start > 0 && start < *len)
    {
        rest = *len - start;
        j = 0;
        while (j < rest)
        {
            buf[j] = buf[start + j];
            j++;
        }
        *len = rest;
    }
    return (1);
}

int		process_stdin(const t_dict *d)
{
    char	*buf;
    int	 cap;
    int	 len;
    int	 n;
    int	 i;
    char	 tmp[READ_BUF_SIZE];

    buf = (char *)malloc(READ_BUF_SIZE);
    if (!buf)
        return (0);
    cap = READ_BUF_SIZE;
    len = 0;
    n = read(0, tmp, READ_BUF_SIZE);
    while (n > 0)
    {
        if (!sm_expand(&buf, &cap, len + n + 1, len))
        {
            free(buf);
            return (0);
        }
        i = 0;
        while (i < n)
        {
            buf[len + i] = tmp[i];
            i++;
        }
        len += n;
        if (!sm_process_pending(d, buf, &len))
        {
            free(buf);
            return (0);
        }
        n = read(0, tmp, READ_BUF_SIZE);
    }
    if (len > 0)
    {
        if (!sm_expand(&buf, &cap, len + 2, len))
        {
            free(buf);
            return (0);
        }
        buf[len] = '\n';
        len += 1;
        if (!sm_process_pending(d, buf, &len))
        {
            free(buf);
            return (0);
        }
    }
    free(buf);
    return (1);
}
