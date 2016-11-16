#include "lemin_intern.h"

static void	rate_neighbors(t_list *neighbors, int path_index, t_list *next)
{
	t_neighbor	*neighbor;
	t_room		*room;
	t_list		*pos;

	pos = neighbors;
	while ((pos = pos->next) && pos != neighbors)
	{
		neighbor = CONTAINER_OF(pos, t_neighbor, list);
		room = neighbor->room;
		if (room->path_index != -1)
			continue ;
		room->path_index = path_index;
		list_add_tail(&room->path, next);
	}
}

extern void	rate_graph(t_room *start)
{
	t_room	*room;
	t_list	cur;
	t_list	next;
	t_list	*pos;
	int		path_index;

	path_index = 1;
	start->path_index = 0;
	INIT_LIST_HEAD(&next);
	list_add_tail(&start->path, &next);
	while (!list_empty(&next))
	{
		INIT_LIST_HEAD(&cur);
		list_splice(&next, &cur);
		pos = &cur;
		while ((pos = pos->next) && pos != &cur)
		{
			room = CONTAINER_OF(pos, t_room, path);
			rate_neighbors(&room->neighbors, path_index, &next);
		}
		path_index += 1;
	}
}
