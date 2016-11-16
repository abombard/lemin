#include "lemin__room.h"
#include "ft_printf.h"

extern void	room_show(t_room *room)
{
	t_neighbor	*n;
	t_room		*r;
	t_list		*pos;

	ft_printf("Room {%s}:\nPos %d %d\nPath Index: %d\nNeighbors:",
			room->name, room->x, room->y, room->path_index);
	pos = &room->neighbors;
	while ((pos = pos->next) && pos != &room->neighbors)
	{
		n = CONTAINER_OF(pos, t_neighbor, list);
		ft_fprintf(2, " %s", n->room->name);
	}
	ft_fprintf(2, "\n");
}

extern void	rooms_show(t_list *head)
{
	t_room	*room;
	t_list	*pos;

	pos = head;
	while ((pos = pos->next) && pos != head)
	{
		room = CONTAINER_OF(pos, t_room, list);
		room_show(room);
	}
}
