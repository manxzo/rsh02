/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rush02.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manzo <manzo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 17:16:14 by manzo             +#+    #+#             */
/*   Updated: 2025/10/26 17:16:14 by manzo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RUSH02_H
# define RUSH02_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

# define READ_BUF_SIZE 4096

typedef struct s_pair
{
	char	*key;
	char	*word;
}t_pair;

typedef struct s_dict
{
	t_pair	*items;
	int		size;
}t_dict;

typedef struct s_print
{
	int first;
}t_print;

/* utils_io.c */
void	ft_putchar(char c);
void	ft_putstr(const char *s);
void	ft_puterr(const char *s);
void	print_word(t_print *p, const char *w);

/* utils_str.c */
int		ft_strlen(const char *s);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_strncmp(const char *s1, const char *s2, int n);
int		ft_is_space(char c);
int		ft_str_is_numeric(const char *s);
char	*ft_strdup(const char *s);
char	*str_trim_spaces(const char *s);

/* dict.c */
void	dict_init(t_dict *d);
void	dict_free(t_dict *d);
int		dict_add(t_dict *d, char *key, char *word);
const char	*dict_find(const t_dict *d, const char *key);

/* dict read/parse */
int		load_dictionary(const char *path, t_dict *d);
int		dict_process_line(t_dict *d, const char *line);

/* dict_line_utils.c (minimal cross-file helpers) */
int		dl_find_colon(const char *s);
char	*dl_substr_dup(const char *s, int start, int end);
char	*dl_extract_number(const char *left);

/* num.c */
char	*normalize_number(const char *input);

/* convert.c */
int		print_number_words(const t_dict *d, const char *num_str);

/* convert_utils.c */
int		print_triad_words(const t_dict *d, int triad, t_print *p);
int		print_scale_word(const t_dict *d, int groups_left, t_print *pr);

/* stdin_mode.c */
int		process_stdin(const t_dict *d);

#endif
