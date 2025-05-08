/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 22:33:42 by afpachec          #+#    #+#             */
/*   Updated: 2025/05/08 12:59:03 by afpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

static void render_rays(t_ftm_image *canvas, t_game *game, t_player *player, t_coords coords, t_size entity_size)
{
    size_t i;
    double scale;

    scale = fmin(entity_size.width, entity_size.height);
    i = -1;
    while (++i < PLAYER_RAYS)
	{
		coords.yaw = player->rays[i].angle;
		ftm_draw_line_angle(canvas, coords, player->rays[i].length * scale, game->minimap.player_ray_color);
	}
}

static void	set_entity_color(t_game *game, t_entity *entity, unsigned *color)
{
	if (entity->type == ENTITY_WALL)
		*color = game->minimap.wall_color;
	else if (entity->type == ENTITY_PLAYER)
		*color = game->minimap.player_color;
	else
		*color = game->minimap.entity_color;
}

static void	render_entity(t_ftm_image *canvas, t_game *game, t_entity *entity, t_coords coords, t_size entity_size)
{
	unsigned	color;
	t_coords		new_coords;

	new_coords = (t_coords){(int)(coords.x + (entity->coords.x * entity_size.width)), (int)(coords.y + (entity->coords.y * entity_size.height)), 0, 0};
	set_entity_color(game, entity, &color);
	if (entity->type == ENTITY_PLAYER)
	{
		render_rays(canvas, game, (t_player *)entity, new_coords, entity_size);
		entity_size = (t_size){0, 0};
	}
	ftm_draw_rectangle(canvas,
			new_coords,
			entity_size,
			(t_ftm_rectangle){color, color, (t_size){1, 1}});
}

static void render_entities(t_ftm_image *canvas, t_game *game, t_coords coords, t_size size)
{
    t_list *entity_item;
    t_entity *entity;
    t_size entity_size;
    t_size add_to_last;
    double scale;

    scale = fmin((double)size.width / (double)game->map->size.width,
                (double)size.height / (double)game->map->size.height);
    entity_size = (t_size){scale, scale};
    add_to_last.width = (size.width - (entity_size.width * game->map->size.width)) / 2;
    add_to_last.height = (size.height - (entity_size.height * game->map->size.height)) / 2;
    entity_item = game->entities;
    while (entity_item)
    {
        entity = entity_item->data;
        if (entity != (t_entity *)game->player)
            render_entity(canvas, game, entity,
                    (t_coords){coords.x + add_to_last.width, coords.y + add_to_last.height, 0, 0},
                    entity_size);
        entity_item = entity_item->next;
    }
    render_entity(canvas, game, (t_entity *)game->player,
        (t_coords){coords.x + add_to_last.width, coords.y + add_to_last.height, 0, 0},
        entity_size);
}

void	render_minimap(t_game *game, t_ftm_image *canvas, t_coords coords, t_size size)
{
	ftm_draw_rectangle(canvas, coords, size, (t_ftm_rectangle){game->minimap.background_color, game->minimap.border_color, (t_size){1, 1}});
	render_entities(canvas, game, coords, size);
}
