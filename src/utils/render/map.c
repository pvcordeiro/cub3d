/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 22:33:42 by afpachec          #+#    #+#             */
/*   Updated: 2025/05/06 17:44:48 by afpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

static void render_map_rays(t_image *canvas, t_entity *entity, t_coords coords, t_size entity_size)
{
    t_player *player;
    size_t i;
    double scale;

    player = entity->private;
    scale = fmin(entity_size.width, entity_size.height);
    i = -1;
    while (++i < PLAYER_RAYS)
		ftm_draw_line_angle(canvas, coords, player->rays[i].angle, player->rays[i].length * scale, 0x0FFF00);
}

static void	render_map_entity(t_image *canvas, t_entity *entity, t_coords coords, t_size entity_size)
{
	unsigned int	color;
	unsigned int	border_color;
	t_coords		new_coords;

	color = 0xFFFFFF;
	border_color = 0xFFFFFF;
	new_coords = (t_coords){(int)(coords.x + (entity->coords.x * entity_size.width)), (int)(coords.y + (entity->coords.y * entity_size.height)), 0, 0};
	if (entity->type == ENTITY_PLAYER)
	{
		color = 0xFF0000;
		border_color = 0xCC0000;
		render_map_rays(canvas, entity, new_coords, entity_size);
		entity_size.width = 1;
		entity_size.height = 1;
	}
	ftm_draw_rectangle(canvas,
			new_coords,
			entity_size,
			color, border_color);
}

static void render_map_entities(t_map *map, t_image *canvas, t_coords coords, t_size size)
{
    t_list *entity_item;
    t_entity *entity;
    t_size entity_size;
    t_size add_to_last;
    double scale;

    scale = fmin((double)size.width / (double)map->size.width,
                (double)size.height / (double)map->size.height);
    entity_size = (t_size){scale, scale};
    add_to_last.width = (size.width - (entity_size.width * map->size.width)) / 2;
    add_to_last.height = (size.height - (entity_size.height * map->size.height)) / 2;
    entity_item = map->entities;
    while (entity_item)
    {
        entity = entity_item->data;
        if (entity != map->player)
            render_map_entity(canvas, entity,
                    (t_coords){coords.x + add_to_last.width, coords.y + add_to_last.height, 0, 0},
                    entity_size);
        entity_item = entity_item->next;
    }
    render_map_entity(canvas, map->player,
        (t_coords){coords.x + add_to_last.width, coords.y + add_to_last.height, 0, 0},
        entity_size);
}

void	render_map(t_map *map, t_image *canvas, t_coords coords, t_size size)
{
	ftm_draw_rectangle(canvas, coords, size, 0x888888, 0xFFFFFF);
	render_map_entities(map, canvas, coords, size);
}
