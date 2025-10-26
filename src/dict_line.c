#include "rush02.h"

int		dict_process_line(t_dict *d, const char *line)
{
	int		cpos;
	char	*left;
	char	*right;
	char	*num;
	char	*word;

	cpos = dl_find_colon(line);
	if (cpos < 0)
		return (1);
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
