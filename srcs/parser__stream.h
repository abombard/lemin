#ifndef PARSER__STREAM_H
# define PARSER__STREAM_H

# include "lemin_intern.h"

# define BUF_SIZE 128

typedef struct	s_stream
{
	int		fd;
	char	buf[BUF_SIZE];
	size_t	buf_size;
	size_t	size;
	size_t	size_left;
}				t_stream;

extern void		stream_init(t_stream *s, int fd);
extern bool		get_next_line(t_stream	*s, t_buf *line);

#endif
