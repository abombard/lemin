#ifndef STATE_H
# define STATE_H

# include "lemin_intern.h"

typedef enum	e_state
{
	STATE_UNDEFINED = 0,
	STATE_COMMENT,
	STATE_ANT_COUNT,
	STATE_ROOM,
	STATE_ROOM_START,
	STATE_ROOM_END,
	STATE_TUBE,
}				t_state;

extern t_state	state_get(const t_buf *s);
extern bool		check_state(t_state state, t_state new_state);

#endif
