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

static void	rate_graph(t_room *start)
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

static bool	get_path(t_room *end, t_room *start, t_list *path)
{
	t_room		*room_cur;
	t_room		*room_iter;
	t_neighbor	*neighbor;
	t_list		*pos;

	fprintf(stderr, "%s\n", __func__);
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

typedef struct	s_path
{
	t_list	head;
	t_list	list;
}				t_path;

static bool	get_paths(t_room *start, t_room *end, t_list *paths)
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

static void	free_path(t_list *path)
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

static void	paths_del(t_list *paths)
{
	t_path	*path;
	t_list	*pos;

	while (!list_empty(paths))
	{
		pos = paths->next;
		path = CONTAINER_OF(pos, t_path, list);
		list_del(&path->list);
		free(path);
	}
}

static void	path_show(t_list *path)
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

static void	paths_show(t_list *paths)
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

static bool	lemin(void)
{
	t_lemin		lemin;
	t_list		paths;

	lemin.ant_count = 0;
	lemin.start = NULL;
	lemin.end = NULL;
	INIT_LIST_HEAD(&lemin.rooms);

	fprintf(stderr, "Parsing file and Building Lemin structure: ");
	ASSERT(parser(0, &lemin));
	ASSERT(lemin.start != NULL && lemin.end != NULL);
	fprintf(stderr, "Ok!\n");

	fprintf(stderr, "Rating each Room of the Graph: ");
	rate_graph(lemin.start);
	fprintf(stderr, "Ok!\n");

	fprintf(stderr, "STARTING ROOM:\n");
	room_show(lemin.start);
	fprintf(stderr, "END ROOM:\n");
	room_show(lemin.end);

	rooms_show(&lemin.rooms);

	fprintf(stderr, "Calculating all possible paths: ");
	ASSERT(get_paths(lemin.start, lemin.end, &paths));
	fprintf(stderr, "Ok!\n");

	fprintf(stderr, "Possible paths are:\n");
	paths_show(&paths);

	paths_del(&paths);
	rooms_del(&lemin.rooms);

	return (true);
}

int main()
{
	return (lemin() == true ? 0 : 1);
}

