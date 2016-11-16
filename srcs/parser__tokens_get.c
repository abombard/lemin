#include "parser__tokens_get.h"
#include "lemin_intern.h"

static bool		get_next_token(char *buf, size_t buf_size,
							size_t *start, size_t *size)
{
	size_t	i;

	i = 0;
	while (i < buf_size)
	{
		if (!ft_isspace(buf[i]) && buf[i] != '-')
			break ;
		i++;
	}
	*start = i;
	while (i < buf_size)
	{
		if (ft_isspace(buf[i]) || buf[i] == '-')
			break ;
		i++;
	}
	*size = i - *start;
	return (*size > 0);
}

extern size_t	tokens_get(char *buf, size_t buf_size, t_buf *token_array)
{
	size_t	token_count;
	size_t	start;
	size_t	size;

	token_count = 0;
	while (get_next_token(buf, buf_size, &start, &size))
	{
		if (token_count < TOKEN_COUNT_MAX)
		{
			token_array[token_count].bytes = buf + start;
			token_array[token_count].size = size;
		}
		token_count += 1;
		if (buf_size <= start + size)
			break ;
		buf += start + size + 1;
		buf_size -= start + size + 1;
	}
	return (token_count);
}
