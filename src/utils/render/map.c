/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 22:33:42 by afpachec          #+#    #+#             */
/*   Updated: 2025/04/30 01:20:57 by afpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

static void	render_map_rectangle(t_image *canvas, t_coords coords, t_size size, unsigned int color)
{
	int	i;
	int	j;

	i = -1;
	while (++i < size.width)
	{
		j = -1;
		while (++j < size.height)
			put_pixel_in_image(canvas, (t_coords){coords.x + i, coords.y + j, 0, 0}, color);
	}
}

static void	render_map_entities(t_map *map, t_image *canvas, t_coords coords, t_size size)
{
	t_list			*entity_item;
	t_entity		*entity;
	t_size			entity_size;
	unsigned int	color;

	entity_size = (t_size){ceil((double)size.width / (double)map->size.width),
			ceil((double)size.height / (double)map->size.height)};
	entity_item = map->entities;
	while (entity_item)
	{
		entity = entity_item->data;
		color = 0xFFFFFF;
		if (entity->type == ENTITY_PLAYER)
			color = 0xFF0000;
		render_map_rectangle(canvas,
				(t_coords){coords.x + (entity->coords.x * entity_size.width), coords.y + (entity->coords.y * entity_size.height), 0, 0},
				entity_size,
				color);
		entity_item = entity_item->next;
	}
}

void	render_map(t_map *map, t_image *canvas, t_coords coords, t_size size)
{
	render_map_rectangle(canvas, coords, size, 0x888888);
	render_map_entities(map, canvas, coords, size);
}
