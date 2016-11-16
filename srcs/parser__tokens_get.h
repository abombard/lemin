#ifndef PARSER__TOKENS_GET_H
# define PARSER__TOKENS_GET_H

# include "lemin_intern.h"
# include <unistd.h>

# define TOKEN_COUNT_MAX		3

extern size_t	tokens_get(char *buf, size_t buf_size, t_buf *token_array);

#endif
