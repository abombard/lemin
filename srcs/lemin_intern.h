#ifndef LEMIN_INTERN_H
# define LEMIN_INTERN_H

# include "libft.h"
# include "list.h"
# include "ft_printf.h"
# include <stdbool.h>

# include "lemin__room.h"

typedef struct	s_lemin
{
	int		ant_count;
	t_room	*start;
	t_room	*end;
	t_list	rooms;
}				t_lemin;

extern bool		parser(int fd, t_lemin *lemin);

extern void		rate_graph(t_room *start, t_room *end);

typedef struct	s_path
{
	t_list	head;
	t_list	list;
}				t_path;

extern bool		get_paths(t_room *start, t_room *end, t_list *paths);
extern void		free_path(t_list *path);
extern void		path_show(t_list *path);
extern void		paths_show(t_list *paths);

#endif
