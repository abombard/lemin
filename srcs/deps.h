#ifndef DEPS_H
# define DEPS_H

# include <unistd.h>
# include <stdbool.h>

typedef struct	s_buf
{
	char	*bytes;
	size_t	size;
}				t_buf;

# define FATAL(...) { ft_fprintf(2, "ERROR:" __VA_ARGS__); return false; }
# define ASSERT(e) {if (!(e)){ft_fprintf(2,"%s failed\n",#e); return 0;}}

#endif
