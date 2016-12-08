#include "lemin_intern.h"

static void	int_cross_road(t_room *room_cur, t_room *room_next,
		t_room *end, bool *on_the_road)
{
	if (room_next != end)
		*on_the_road = true;
	room_next->ant_id = room_cur->ant_id;
	room_cur->ant_id = 0;
	ft_printf("L%d-%s ", room_next->ant_id, room_next->name);
}

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
		int_cross_road(room_cur, room_next, end, &on_the_road);
	}
	if (ant_id != 0)
	{
		on_the_road = true;
		ft_printf("L%d-%s ", ant_id, room_cur->name);
	}
	ft_printf("\n");
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
	ASSERT(parser(0, &lemin));
	ft_printf("\n");
	if (lemin.ant_count <= 0)
		FATAL("Ant count %d\n", lemin.ant_count);
	if (lemin.start == NULL || lemin.end == NULL)
		FATAL("Need a ##start and an ##end node\n");
	rate_graph(lemin.end, lemin.start);
	lemin.start->path_index = lemin.ant_count;
	ASSERT(get_paths(lemin.start, lemin.end, &paths));
	if (list_len(&paths) <= 0)
		FATAL("Found no possible path\n");
	cross_roads(&paths, lemin.end, lemin.ant_count);
	rooms_del(&lemin.rooms);
	return (true);
}

int			main(void)
{
	return (lemin() == true ? 0 : 1);
}
