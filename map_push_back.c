/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_pushback.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absaid <absaid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 11:07:00 by absaid            #+#    #+#             */
/*   Updated: 2022/11/28 11:15:49 by absaid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void map_push_back(t_map **head, int **coord, size_t len)
{
	t_map *node = ft_calloc(1, sizeof(t_map)); // TODO: use builtin.
	if (!node)
		return;
	node->coord = coord;
	node->len = len;
	if (!*head)
	{
		*head = node;
		return;
	}
	t_map *last = *head;
	while (last->next)
		last = last->next;
	last->next = node;
}