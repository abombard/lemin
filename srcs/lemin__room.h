#ifndef LEMIN__ROOM_H
# define LEMIN__ROOM_H

# include "deps.h"
# include "list.h"
# include <unistd.h>
# include <stdbool.h>

# define ROOM_NAME_SIZE_MAX		31

typedef struct	s_room
{
	char	name[ROOM_NAME_SIZE_MAX + 1];
	int		x;
	int		y;
	t_list	list;
	t_list	neighbors;

	int		path_index;
	t_list	path;

	bool	taken;
}				t_room;

typedef struct	s_neighbor
{
	t_room	*room;
	t_list	list;
}				t_neighbor;

extern t_room	*room_add(t_list *head, t_buf *token_array);
extern void		rooms_del(t_list *head);
extern bool		room_link(t_list *head, t_buf *room_name1, t_buf *room_name2);
extern void		room_show(t_room *room);
extern void		rooms_show(t_list *head);

#endif
