#include "rush02.h"

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
	ok = dr_read_all(fd, &buf, &len);
	close(fd);
	if (!ok)
		return (0);
	ok = dr_process_buffer(d, buf, len);
	free(buf);
	return (ok);
}
