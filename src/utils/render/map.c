/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 22:33:42 by afpachec          #+#    #+#             */
/*   Updated: 2025/04/30 11:30:37 by afpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

static void	render_map_rectangle(t_image *canvas, t_coords coords, t_size size, unsigned int color, unsigned int border_color)
{
	int				i;
	int				j;
	unsigned int	tmp_color;

	i = -1;
	while (++i < size.width)
	{
		j = -1;
		while (++j < size.height)
		{
			tmp_color = color;
			if (i == 0 || i == size.width - 1 || j == 0 || j == size.height - 1)
				tmp_color = border_color;
			put_pixel_in_image(canvas, (t_coords){coords.x + i, coords.y + j, 0, 0}, tmp_color);
		}
	}
}

static void	render_map_entity(t_image *canvas, t_entity *entity, t_coords coords, t_size entity_size)
{
	unsigned int	color;
	unsigned int	border_color;

	color = 0xFFFFFF;
	border_color = 0xFFFFFF;
	if (entity->type == ENTITY_PLAYER)
	{
		color = 0xFF0000;
		border_color = 0xCC0000;
	}
	render_map_rectangle(canvas,
			(t_coords){(int)(coords.x + (entity->coords.x * entity_size.width)), (int)(coords.y + (entity->coords.y * entity_size.height)), 0, 0},
			entity_size,
			color, border_color);
}

static void	render_map_entities(t_map *map, t_image *canvas, t_coords coords, t_size size)
{
	t_list			*entity_item;
	t_entity		*entity;
	t_size			entity_size;
	t_size			add_to_last;

	entity_size = (t_size){(double)size.width / (double)map->size.width,
			(double)size.height / (double)map->size.height};
	if (entity_size.width * map->size.width < size.width)
		add_to_last = (t_size){size.width - (entity_size.width * map->size.width), add_to_last.height};
	if (entity_size.height * map->size.height < size.height)
		add_to_last = (t_size){add_to_last.width, size.height - (entity_size.height * map->size.height)};
	entity_item = map->entities;
	while (entity_item)
	{
		entity = entity_item->data;
		render_map_entity(canvas, entity,
				(t_coords){coords.x + add_to_last.width / 2, coords.y + add_to_last.height / 2, 0, 0},
				entity_size);
		entity_item = entity_item->next;
	}
}

void	render_map(t_map *map, t_image *canvas, t_coords coords, t_size size)
{
	printf("PLAYER -> x: %f y: %f yaw: %f\n",
		cub3d()->player->coords.x,
		cub3d()->player->coords.y,
		cub3d()->player->coords.yaw);
	render_map_rectangle(canvas, coords, size, 0x888888, 0xFFFFFF);
	render_map_entities(map, canvas, coords, size);
}
