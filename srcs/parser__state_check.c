#include "parser__state.h"

static bool	check_state_undefined(t_state new_state)
{
	return (new_state == STATE_ANT_COUNT);
}

static bool	check_state_ant_count(t_state new_state)
{
	if (new_state == STATE_ROOM ||
		new_state == STATE_ROOM_START ||
		new_state == STATE_ROOM_END)
		return (true);
	return (false);
}

static bool	check_state_room(t_state new_state)
{
	if (new_state == STATE_ROOM ||
		new_state == STATE_ROOM_START ||
		new_state == STATE_ROOM_END ||
		new_state == STATE_TUBE)
		return (true);
	return (false);
}

static bool	check_state_tube(t_state new_state)
{
	return (new_state == STATE_TUBE);
}

extern bool	check_state(t_state state, t_state new_state)
{
	if (state == STATE_UNDEFINED)
		return (check_state_undefined(new_state));
	if (state == STATE_ANT_COUNT)
		return (check_state_ant_count(new_state));
	if (state == STATE_ROOM ||
		state == STATE_ROOM_START ||
		state == STATE_ROOM_END)
		return (check_state_room(new_state));
	if (state == STATE_TUBE)
		return (check_state_tube(new_state));
	return (false);
}
