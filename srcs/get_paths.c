/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_paths.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abombard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/08 18:10:35 by abombard          #+#    #+#             */
/*   Updated: 2016/12/08 18:10:36 by abombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin_intern.h"
#include <stdio.h>

static void	int_get_path(t_room *room_cur, t_room **room_next)
{
	int			lower_path_index;
	t_neighbor	*neighbor;
	t_room		*room_iter;
	t_list		*pos;

	*room_next = NULL;
	lower_path_index = 2000000;
	pos = &room_cur->neighbors;
	while ((pos = pos->next) && pos != &room_cur->neighbors)
	{
		neighbor = CONTAINER_OF(pos, t_neighbor, list);
		room_iter = neighbor->room;
		if (room_iter->taken == true ||
			room_iter->path_index > lower_path_index)
			continue ;
		lower_path_index = room_iter->path_index;
		*room_next = room_iter;
	}
}

static bool	get_path(t_room *room_cur, t_room *end, t_list *path)
{
	t_room		*room_next;

	if (room_cur == NULL)
		return (false);
	if (room_cur == end)
		return (true);
	room_cur->taken = true;
	list_add_tail(&room_cur->path, path);
	int_get_path(room_cur, &room_next);
	if (get_path(room_next, end, path))
		return (true);
	list_del(&room_cur->path);
	room_cur->taken = false;
	return (false);
}

extern bool	get_paths(t_room *start, t_room *end, t_list *paths)
{
	t_path	*new_path;

	INIT_LIST_HEAD(paths);
	while (true)
	{
		new_path = (t_path *)malloc(sizeof(t_path));
		if (new_path == NULL)
		{
			perror("malloc");
			return (false);
		}
		INIT_LIST_HEAD(&new_path->head);
		if (!get_path(start, end, &new_path->head))
		{
			free(new_path);
			break ;
		}
		list_del(new_path->head.next);
		list_add_tail(&new_path->list, paths);
	}
	return (true);
}
