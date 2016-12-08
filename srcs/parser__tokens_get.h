/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser__tokens_get.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abombard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/08 18:12:46 by abombard          #+#    #+#             */
/*   Updated: 2016/12/08 18:12:47 by abombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER__TOKENS_GET_H
# define PARSER__TOKENS_GET_H

# include "lemin_intern.h"
# include <unistd.h>

# define TOKEN_COUNT_MAX		3

extern size_t	tokens_get(char *buf, size_t buf_size, t_buf *token_array);

#endif
