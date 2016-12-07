#ifndef PARSER__STATE_H
# define PARSER__STATE_H

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

struct			s_state
{
	t_state	state;
	bool	(*test)(const t_buf *);
};

extern t_state	state_get(const t_buf *s);
extern bool		check_state(t_state state, t_state new_state);

bool			is_comment(const t_buf *s);
bool			is_ant_count(const t_buf *s);
bool			is_room(const t_buf *s);
bool			is_start(const t_buf *s);
bool			is_end(const t_buf *s);

#endif
