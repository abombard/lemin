#include "parser__state.h"
#include "libft.h"

static bool		is_tube(const t_buf *s)
{
	int	i;

	i = 0;
	if (ft_isspace(s->bytes[i]))
		return (false);
	while (i < s->size && s->bytes[i] != '-')
		i++;
	if (i == s->size)
		return (false);
	i++;
	if (i == s->size)
		return (false);
	while (i < s->size)
		i++;
	return (i == s->size ? true : false);
}

extern t_state	state_get(const t_buf *s)
{
	static struct s_state	state_array[] = {
		{ STATE_COMMENT, is_comment },
		{ STATE_ANT_COUNT, is_ant_count },
		{ STATE_ROOM, is_room },
		{ STATE_ROOM_START, is_start },
		{ STATE_ROOM_END, is_end },
		{ STATE_TUBE, is_tube }
	};
	size_t					i;

	if (s->size == 0)
		return (STATE_UNDEFINED);
	i = 0;
	while (i < sizeof(state_array) / sizeof(state_array[0]))
	{
		if (state_array[i].test(s))
			return (state_array[i].state);
		i++;
	}
	return (STATE_UNDEFINED);
}
