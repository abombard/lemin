/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abombard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/08 18:12:26 by abombard          #+#    #+#             */
/*   Updated: 2016/12/08 18:12:27 by abombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin_intern.h"

extern void	free_path(t_list *path)
{
	t_room	*room;
	t_list	*pos;

	pos = path;
	while ((pos = pos->next) && pos != path)
	{
		room = CONTAINER_OF(pos, t_room, path);
		room->taken = false;
	}
	list_del(path);
}

extern void	path_show(t_list *path)
{
	t_room	*room;
	t_list	*pos;

	ft_fprintf(2, "New path:");
	pos = path;
	while ((pos = pos->next) && pos != path)
	{
		room = CONTAINER_OF(pos, t_room, path);
		ft_fprintf(2, " %s {%d}", room->name, room->path_index);
	}
	ft_fprintf(2, "\n");
}

extern void	paths_show(t_list *paths)
{
	t_path	*path;
	t_list	*pos;

	ft_fprintf(2, "%s\n", __func__);
	pos = paths;
	while ((pos = pos->next) && pos != paths)
	{
		path = CONTAINER_OF(pos, t_path, list);
		path_show(&path->head);
	}
}
