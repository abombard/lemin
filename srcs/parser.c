/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abombard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/08 18:12:09 by abombard          #+#    #+#             */
/*   Updated: 2016/12/08 18:12:10 by abombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin_intern.h"
#include "parser__stream.h"
#include "parser__state.h"
#include "parser__tokens_get.h"

#include "deps.h"

static char	*state_to_string(t_state state)
{
	static char *array[] = {
		[STATE_UNDEFINED] = "STATE_UNDEFINED",
		[STATE_ANT_COUNT] = "STATE_ANT_COUNT",
		[STATE_ROOM] = "STATE_ROOM",
		[STATE_ROOM_START] = "STATE_ROOM_START",
		[STATE_ROOM_END] = "STATE_ROOM_END",
		[STATE_TUBE] = "STATE_TUBE",
		[STATE_COMMENT] = "STATE_COMMENT"
	};

	if (state > STATE_COMMENT)
		return ("Unknown State");
	return (array[state]);
}

static bool	set_room(t_room *new, t_room **room)
{
	if (*room != NULL)
		FATAL("Can only have 1 room ##start and 1 room ##end\n");
	*room = new;
	return (true);
}

static bool	build_lemin(t_buf *token_array,
		t_state state, t_state new_state, t_lemin *lemin)
{
	t_room	*room;

	if (new_state == STATE_ANT_COUNT)
		lemin->ant_count = ft_atoi(token_array[0].bytes);
	else if (new_state == STATE_ROOM)
	{
		room = room_add(&lemin->rooms, token_array);
		if (room == NULL)
			return (false);
		if (state == STATE_ROOM_START)
		{
			ASSERT(set_room(room, &lemin->start));
		}
		else if (state == STATE_ROOM_END)
		{
			ASSERT(set_room(room, &lemin->end));
		}
	}
	else if (new_state == STATE_TUBE)
	{
		ASSERT(room_link(&lemin->rooms, &token_array[0], &token_array[1]));
	}
	return (true);
}

extern bool	parser(int fd, t_lemin *lemin)
{
	t_stream	stream;
	t_buf		line;
	t_buf		token_array[TOKEN_COUNT_MAX];
	t_state		state;
	t_state		new_state;

	state = STATE_UNDEFINED;
	stream_init(&stream, fd);
	while (get_next_line(&stream, &line))
	{
		line.bytes[line.size] = '\0';
		ft_printf("%s\n", line.bytes);
		new_state = state_get(&line);
		if (new_state == STATE_UNDEFINED)
			FATAL("Invalid line {%s}\n", line.bytes);
		if (new_state == STATE_COMMENT)
			continue ;
		if (!check_state(state, new_state))
			FATAL("state %s new_state %s\n",
				state_to_string(state), state_to_string(new_state));
		ASSERT(tokens_get(line.bytes, line.size, token_array) > 0);
		ASSERT(build_lemin(token_array, state, new_state, lemin));
		state = new_state;
	}
	return (true);
}
