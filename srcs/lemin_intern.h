#ifndef LEMIN_INTERN_H
# define LEMIN_INTERN_H

# include "libft.h"
# include "list.h"
# include "ft_printf.h"
# include <stdbool.h>

# include <stdio.h> //TEMP

# include "lemin__room.h"

typedef struct	s_lemin
{
	int		ant_count;
	t_room	*start;
	t_room	*end;
	t_list	rooms;
}				t_lemin;

extern bool	parser(int fd, t_lemin *lemin);

#endif

