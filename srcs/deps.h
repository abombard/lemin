#ifndef DEPS_H
# define DEPS_H

# include <stdio.h>
# include <unistd.h>
# include <stdbool.h>

typedef struct	s_buf
{
	char	*bytes;
	size_t	size;
}				t_buf;

# define ASSERT(expr) do { if (!(expr)) { fprintf(stderr, "%s failed\n", #expr); return (false); } } while (0)

#endif
