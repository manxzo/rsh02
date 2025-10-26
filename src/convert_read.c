#include "rush02.h"

int	cr_has_more_nonzero(const char *s, int pos, int len)
{
	int i;

	i = pos;
	while (i < len)
	{
		if (s[i] != '0')
			return (1);
		i++;
	}
	return (0);
}

int	cr_read_first_triad(const char *s, int first_len, int *pos)
{
	int i;
	int triad;

	triad = 0;
	i = 0;
	while (i < first_len)
	{
		triad = triad * 10 + (s[*pos] - '0');
		*pos = *pos + 1;
		i++;
	}
	return (triad);
}

int	cr_read_next_triad(const char *s, int *pos)
{
	int triad;

	triad = (s[*pos] - '0') * 100 + (s[*pos + 1] - '0') * 10
		+ (s[*pos + 2] - '0');
	*pos += 3;
	return (triad);
}
