#include "lemin_intern.h"

static bool	get_path(t_room *end, t_room *start, t_list *path)
{
	t_room		*room_cur;
	t_room		*room_iter;
	t_neighbor	*neighbor;
	t_list		*pos;

	INIT_LIST_HEAD(path);
	if (end == start)
		return (true);
	room_cur = end;
	pos = &room_cur->neighbors;
	while ((pos = pos->next) && pos != &room_cur->neighbors)
	{
		neighbor = CONTAINER_OF(pos, t_neighbor, list);
		room_iter = neighbor->room;
		if (room_iter->taken == true ||
			room_iter->path_index != room_cur->path_index - 1)
			continue ;
		if (room_iter == start)
			return (true);
		room_iter->taken = true;
		list_add(&room_iter->path, path);
		room_cur = room_iter;
		pos = &room_cur->neighbors;
	}
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
		if (!get_path(end, start, &new_path->head))
		{
			free(new_path);
			break ;
		}
		list_add_tail(&new_path->list, paths);
	}
	return (true);
}
