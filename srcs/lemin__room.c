#include "lemin_intern.h"
#include <stdlib.h>

static bool		add_neighbor(t_room *room, t_room *n)
{
	t_neighbor	*neighbor;

	neighbor = (t_neighbor *)malloc(sizeof(t_neighbor));
	if (neighbor == NULL)
	{
		perror("malloc");
		return (false);
	}
	neighbor->room = n;
	list_add_tail(&neighbor->list, &room->neighbors);
	return (true);
}

static void		room_token_to_name(t_buf *token, char *name)
{
	if (token->size > ROOM_NAME_SIZE_MAX)
	{
		ft_memcpy(name, token->bytes, ROOM_NAME_SIZE_MAX);
		name[ROOM_NAME_SIZE_MAX - 1] = '$';
		name[ROOM_NAME_SIZE_MAX] = '\0';
	}
	else
	{
		ft_memcpy(name, token->bytes, token->size);
		name[token->size] = '\0';
	}
}

extern bool		room_link(t_list *head, t_buf *room_name1, t_buf *room_name2)
{
	t_room		*room1;
	t_room		*room2;
	t_room		*room;
	t_list		*pos;

	room_token_to_name(room_name1, room_name1->bytes);
	room_token_to_name(room_name2, room_name2->bytes);
	room1 = NULL;
	room2 = NULL;
	pos = head;
	while ((pos = pos->next) && pos != head)
	{
		room = CONTAINER_OF(pos, t_room, list);
		if (!ft_strcmp(room->name, room_name1->bytes))
			room1 = room;
		if (!ft_strcmp(room->name, room_name2->bytes))
			room2 = room;
	}
	ASSERT(room1 != NULL || room2 != NULL);
	ASSERT(add_neighbor(room1, room2));
	ASSERT(add_neighbor(room2, room1));
	return (true);
}

extern t_room	*room_add(t_list *head, t_buf *token_array)
{
	t_room	*room;

	room = (t_room *)malloc(sizeof(t_room));
	if (room == NULL)
		return (NULL);
	room_token_to_name(&token_array[0], room->name);
	room->x = ft_atoi(token_array[1].bytes);
	room->y = ft_atoi(token_array[2].bytes);
	INIT_LIST_HEAD(&room->neighbors);
	room->path_index = -1;
	INIT_LIST_HEAD(&room->path);
	room->taken = false;
	room->ant_id = 0;
	list_add_tail(&room->list, head);
	return (room);
}

extern void		rooms_del(t_list *head)
{
	t_room		*room;
	t_neighbor	*n;
	t_list		*neighbors;

	while (head->next != head)
	{
		room = CONTAINER_OF(head->next, t_room, list);
		neighbors = &room->neighbors;
		while (neighbors->next != neighbors)
		{
			n = CONTAINER_OF(neighbors->next, t_neighbor, list);
			list_del(&n->list);
			free(n);
		}
		list_del(&room->list);
		free(room);
	}
}
