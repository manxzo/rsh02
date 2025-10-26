#include "rush02.h"

static char	*dup_key(const char *key)
{
	int		len;
	char	*out;
	int		i;

	len = ft_strlen(key);
	out = (char *)malloc(len + 1);
	if (!out)
		return (0);
	i = 0;
	while (i < len)
	{
		out[i] = key[i];
		i++;
	}
	out[i] = '\0';
	return (out);
}

void	dict_init(t_dict *d)
{
	d->items = 0;
	d->size = 0;
}

void	dict_free(t_dict *d)
{
	int i;

	i = 0;
	while (i < d->size)
	{
		free(d->items[i].key);
		free(d->items[i].word);
		i++;
	}
	free(d->items);
	d->items = 0;
	d->size = 0;
}

int	dict_add(t_dict *d, char *key, char *word)
{
	char	*dk;
	char	*dw;
	int		i;
	t_pair	*new_items;

	i = 0;
	while (i < d->size)
	{
		if (ft_strcmp(d->items[i].key, key) == 0)
			return (0);
		i++;
	}
	dk = dup_key(key);
	dw = ft_strdup(word);
	if (!dk || !dw)
	{
		free(dk);
		free(dw);
		return (0);
	}
	new_items = (t_pair *)malloc(sizeof(t_pair) * (d->size + 1));
	if (!new_items)
	{
		free(dk);
		free(dw);
		return (0);
	}
	i = 0;
	while (i < d->size)
	{
		new_items[i] = d->items[i];
		i++;
	}
	free(d->items);
	d->items = new_items;
	d->items[d->size].key = dk;
	d->items[d->size].word = dw;
	d->size += 1;
	return (1);
}

const char	*dict_find(const t_dict *d, const char *key)
{
	int i;

	i = 0;
	while (i < d->size)
	{
		if (ft_strcmp(d->items[i].key, key) == 0)
			return (d->items[i].word);
		i++;
	}
	return (0);
}
