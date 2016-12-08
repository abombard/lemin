/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser__state_get_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abombard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/08 18:12:58 by abombard          #+#    #+#             */
/*   Updated: 2016/12/08 18:12:59 by abombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser__state.h"
#include "libft.h"

bool		is_comment(const t_buf *s)
{
	return (s->bytes[0] == '#' && s->bytes[1] != '#');
}

bool		is_ant_count(const t_buf *s)
{
	int	i;

	i = 0;
	if (!ft_isdigit(s->bytes[i]))
		return (false);
	while (ft_isdigit(s->bytes[i]) && i < s->size)
		i++;
	return (i == s->size ? true : false);
}

bool		is_room(const t_buf *s)
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

bool		is_start(const t_buf *s)
{
	if (s->size != sizeof("##start") - 1)
		return (false);
	if (ft_memcmp(s->bytes, "##start", sizeof("##start") - 1))
		return (false);
	return (true);
}

bool		is_end(const t_buf *s)
{
	if (s->size != sizeof("##end") - 1)
		return (false);
	if (ft_memcmp(s->bytes, "##end", sizeof("##end") - 1))
		return (false);
	return (true);
}
