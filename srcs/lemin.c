#include "lemin_intern.h"

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

int			main()
{
	return (lemin() == true ? 0 : 1);
}
