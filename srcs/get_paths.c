#include "lemin_intern.h"

static bool	get_path(t_room *room_cur, t_room *start, t_list *path)
{
	t_room		*room_iter;
	t_room		*room_next;
	t_neighbor	*neighbor;
	t_list		*pos;
	int			lower_path_index;

	if (room_cur == NULL)
		return (false);
	if (room_cur == start)
		return (true);
	room_cur->taken = true;
	list_add(&room_cur->path, path);
	lower_path_index = 2000000;
	room_next = NULL;
	pos = &room_cur->neighbors;
	while ((pos = pos->next) && pos != &room_cur->neighbors)
	{
		neighbor = CONTAINER_OF(pos, t_neighbor, list);
		room_iter = neighbor->room;
		if (room_iter->taken == true)
			continue ;
		if (room_iter->path_index < lower_path_index)
		{
			lower_path_index = room_iter->path_index;
			room_next = room_iter;
		}
	}
	if (get_path(room_next, start, path))
		return (true);
	list_del(&room_cur->path);
	room_cur->taken = false;
	return (false);
}

extern bool	get_paths(t_room *start, t_room *end, t_list *paths)
{
	t_path	*new_path;

	INIT_LIST_HEAD(paths);
	while (true)
	{
		new_path = (t_path *)malloc(sizeof(t_path));
		if (new_path == NULL)
		{
			perror("malloc");
			return (false);
		}
		INIT_LIST_HEAD(&new_path->head);
		if (!get_path(end, start, &new_path->head))
		{
			free(new_path);
			break ;
		}
		list_del(new_path->head.prev);
		list_add_tail(&new_path->list, paths);
	}
	return (true);
}
