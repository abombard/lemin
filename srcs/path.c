#include "lemin_intern.h"

extern void	free_path(t_list *path)
{
	t_room	*room;
	t_list	*pos;

	fprintf(stderr, "%s\n", __func__);
	pos = path;
	while ((pos = pos->next) && pos != path)
	{
		room = CONTAINER_OF(pos, t_room, path);
		room->taken = false;
	}
	list_del(path);
}

extern void	path_show(t_list *path)
{
	t_room	*room;
	t_list	*pos;

	fprintf(stderr, "New path:");
	pos = path;
	while ((pos = pos->next) && pos != path)
	{
		room = CONTAINER_OF(pos, t_room, path);
		fprintf(stderr, " %s", room->name);
	}
	fprintf(stderr, "\n");
}

extern void	paths_show(t_list *paths)
{
	t_path	*path;
	t_list	*pos;

	fprintf(stderr, "%s\n", __func__);
	pos = paths;
	while ((pos = pos->next) && pos != paths)
	{
		path = CONTAINER_OF(pos, t_path, list);
		path_show(&path->head);
	}
}
