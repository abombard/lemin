#include "lemin_intern.h"

static bool	cross_road(t_list *path, t_room *end, int ant_id)
{
	t_room	*room_cur;
	t_room	*room_next;
	t_list	*pos;
	bool	on_the_road;

	list_add_tail(&end->path, path);
	on_the_road = false;
	pos = path->prev;
	while ((pos = pos->prev) && pos != path)
	{
		room_cur = CONTAINER_OF(pos, t_room, path);
		if (room_cur->ant_id == 0)
			continue ;
		room_next = CONTAINER_OF(pos->next, t_room, path);
		if (room_next != end)
			on_the_road = true;
		room_next->ant_id = room_cur->ant_id;
		room_cur->ant_id = 0;
		fprintf(stdout, "L%d-%s ", room_next->ant_id, room_next->name);
	}
	if (ant_id != 0)
	{
		on_the_road = true;
		fprintf(stdout, "L%d-%s ", ant_id, room_cur->name);
	}
	room_cur->ant_id = ant_id;
	list_del(&end->path);
	return (on_the_road);
}

static void	cross_roads(t_list *paths, t_room *end, int ant_count)
{
	int			ant_id;
	t_path		*path;
	t_list		*pos;

	ant_id = 1;
	while (!list_empty(paths))
	{
		pos = paths;
		while ((pos = pos->next) && pos != paths)
		{
			path = CONTAINER_OF(pos, t_path, list);
			if (!cross_road(&path->head, end, ant_id))
			{
				pos = pos->prev;
				list_del(&path->list);
				free(path);
			}
			if (ant_id == ant_count || ant_id == 0)
				ant_id = 0;
			else
				ant_id += 1;
		}
		fprintf(stdout, "\n");
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

	ASSERT(lemin.start->path_index != -1);
	ASSERT(lemin.end->path_index != -1);

	fprintf(stderr, "STARTING ROOM:\n");
	room_show(lemin.start);
	fprintf(stderr, "END ROOM:\n");
	room_show(lemin.end);

	fprintf(stderr,"LIST ROOM\n");
	rooms_show(&lemin.rooms);

	fprintf(stderr, "Calculating all possible paths: ");
	ASSERT(get_paths(lemin.start, lemin.end, &paths));
	fprintf(stderr, "Ok!\n");

	fprintf(stderr, "Possible paths are:\n");
	paths_show(&paths);

	fprintf(stderr, "Cross roads\n");
	cross_roads(&paths, lemin.end, lemin.ant_count);
	fprintf(stderr, "Ok!\n");

	rooms_del(&lemin.rooms);

	return (true);
}

int			main()
{
	return (lemin() == true ? 0 : 1);
}
