#include "rush02.h"

static char	*strip_outer_spaces(const char *s)
{
	char	*trim;

	trim = str_trim_spaces(s);
	return (trim);
}

static char	*remove_leading_zeros(const char *s)
{
	int	 i;
	int	 len;
	char	*out;
	int	 j;

	i = 0;
	while (s[i] == '0')
		i++;
	len = ft_strlen(s + i);
	if (len == 0)
		return (ft_strdup("0"));
	out = (char *)malloc(len + 1);
	if (!out)
		return (0);
	j = 0;
	while (j < len)
	{
		out[j] = s[i + j];
		j++;
	}
	out[j] = '\0';
	return (out);
}

char	*normalize_number(const char *input)
{
	char	*trim;
	int		i;
	char	*out;

	trim = strip_outer_spaces(input);
	if (!trim)
		return (0);
	i = 0;
	while (trim[i])
	{
		if (trim[i] < '0' || trim[i] > '9')
			return (free(trim), (char *)0);
		i++;
	}
	out = remove_leading_zeros(trim);
	free(trim);
	return (out);
}
