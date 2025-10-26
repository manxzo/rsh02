#include "rush02.h"

static int	print_error(const char *msg)
{
	ft_puterr(msg);
	return (1);
}

int		main(int argc, char **argv)
{
	const char	*dict_path;
	const char	*input;
	char		*norm;
	t_dict		dict;

	if (argc == 2)
	{
		dict_path = "numbers.dict";
		input = argv[1];
	}
	else if (argc == 3)
	{
		dict_path = argv[1];
		input = argv[2];
	}
	else
		return (print_error("Error\n"));
	if (!load_dictionary(dict_path, &dict))
		return (print_error("Dict Error\n"));
	if (input[0] == '-' && input[1] == '\0')
	{
		if (!process_stdin(&dict))
		{
			dict_free(&dict);
			return (print_error("Error\n"));
		}
		dict_free(&dict);
		return (0);
	}
	norm = normalize_number(input);
	if (!norm)
		return (dict_free(&dict), print_error("Error\n"));
	if (!print_number_words(&dict, norm))
		return (dict_free(&dict), free(norm), print_error("Dict Error\n"));
	ft_putchar('\n');
	dict_free(&dict);
	free(norm);
	return (0);
}
