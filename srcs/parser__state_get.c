#include "parser__state.h"
#include "libft.h"

static bool		is_comment(const t_buf *s)
{
	return (s->bytes[0] == '#' && s->bytes[1] != '#');
}

static bool		is_ant_count(const t_buf *s)
{
	int	i;

	i = 0;
	if (!ft_isdigit(s->bytes[i]))
		return (false);
	while (ft_isdigit(s->bytes[i]) && i < s->size)
		i++;
	return (i == s->size  ? true : false);
}

static bool		is_room(const t_buf *s)
{
	int	i;

	i = 0;
	if (ft_isspace(s->bytes[i]))
		return (false);
	while (!ft_isspace(s->bytes[i]) && i < s->size)
		i++;
	while (ft_isspace(s->bytes[i]) && i < s->size)
		i++;
	if (!ft_isdigit(s->bytes[i]))
		return (false);
	while (ft_isdigit(s->bytes[i]) && i < s->size)
		i++;
	if (!ft_isspace(s->bytes[i]))
		return (false);
	while (ft_isspace(s->bytes[i]) && i < s->size)
		i++;
	if (!ft_isdigit(s->bytes[i]))
		return (false);
	while (ft_isdigit(s->bytes[i]) && i < s->size)
		i++;
	return (i == s->size ? true : false);
}

static bool		is_start(const t_buf *s)
{
	if (s->size != sizeof ("##start") - 1)
		return (false);
	if (ft_memcmp(s->bytes, "##start", sizeof("##start") - 1))
		return (false);
	return (true);
}

static bool		is_end(const t_buf *s)
{
	if (s->size != sizeof ("##end") - 1)
		return (false);
	if (ft_memcmp(s->bytes, "##end", sizeof("##end") - 1))
		return (false);
	return (true);
}

static bool		is_tube(const t_buf *s)
{
	int	i;

	i = 0;
	if (!ft_isdigit(s->bytes[i]))
		return (false);
	while (ft_isdigit(s->bytes[i]))
		i++;
	if (s->bytes[i] != '-')
		return (false);
	i++;
	if (!ft_isdigit(s->bytes[i]))
		return (false);
	while (ft_isdigit(s->bytes[i]))
		i++;
	return (i == s->size ? true : false);
}

extern t_state	state_get(const t_buf *s)
{
	static struct {
		t_state	state;
		bool	(*test)(const t_buf *);
	} state_array[] = {
		{ STATE_COMMENT, is_comment },
		{ STATE_ANT_COUNT, is_ant_count },
		{ STATE_ROOM, is_room },
		{ STATE_ROOM_START, is_start },
		{ STATE_ROOM_END, is_end },
		{ STATE_TUBE, is_tube }
	};
	size_t	i;

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

