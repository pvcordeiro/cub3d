/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvcordeiro <pvcordeiro@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 22:33:42 by afpachec          #+#    #+#             */
/*   Updated: 2025/05/27 19:18:20 by pvcordeiro       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

static void	set_entity_color(t_game *game, t_entity *entity, unsigned *color)
{
	if (entity->type == ENTITY_WALL)
		*color = game->minimap.wall_color;
	else if (entity->type == ENTITY_PLAYER)
		*color = game->minimap.player_color;
	else if (entity->type == ENTITY_DOOR)
		*color = game->minimap.door_color;
	else
		*color = game->minimap.entity_color;
}

static bool in_boundaries(t_coords entity_pos, t_coords minimap_pos, t_size minimap_size)
{
    return (entity_pos.x + 100>= minimap_pos.x &&
            entity_pos.y + 100 >= minimap_pos.y &&
            entity_pos.x - 100 < minimap_pos.x + minimap_size.width &&
            entity_pos.y - 100 < minimap_pos.y + minimap_size.height);
}

static void fix_clipping(t_coords *pos, t_size *size, t_coords minimap_pos, t_size minimap_size)
{
	int	clip_left;
	int	clip_right;
	int	clip_top;
	int	clip_bottom;
	
	clip_left = minimap_pos.x - pos->x;
	clip_right = (pos->x + size->width) - (minimap_pos.x + minimap_size.width);
	clip_top = minimap_pos.y - pos->y;
	clip_bottom = (pos->y + size->height) - (minimap_pos.y + minimap_size.height);
	if (clip_left > 0) 
	{
		pos->x += clip_left;
		size->width -= clip_left;
	}
	if (clip_right > 0)
		size->width -= clip_right;
	if (clip_top > 0)
	{
		pos->y += clip_top;
		size->height -= clip_top;
	}
	if (clip_bottom > 0)
		size->height -= clip_bottom;
}

static void	render_entity(t_ftm_image *canvas, t_game *game, t_entity *entity, t_coords minimap_coords, t_size minimap_size, t_coords coords, t_size entity_size)
{
	unsigned int	color;
	t_coords		new_coords;
    t_size          draw_size;

	new_coords = (t_coords){(int)(coords.x + (entity->coords.x * entity_size.width)), (int)(coords.y + (entity->coords.y * entity_size.height)), entity->coords.yaw};
    if (!in_boundaries(new_coords, minimap_coords, minimap_size))
        return ;
    set_entity_color(game, entity, &color);
	if (entity->type == ENTITY_PLAYER)
	{
		ftm_draw_arrow(canvas,
				new_coords,
				(t_size){entity_size.width / 1.5, entity_size.height / 1.5},
				color);
		return ;
	}
    draw_size = (t_size){entity_size.width * entity->size.width,
    entity_size.height * entity->size.height};
    fix_clipping(&new_coords, &draw_size, minimap_coords, minimap_size);
	ftm_draw_rectangle(canvas,
			new_coords,
			draw_size,
			(t_ftm_rectangle){color, color, (t_size){1, 1}});
}

static void render_entities(t_ftm_image *canvas, t_game *game, t_coords minimap_coords, t_size minimap_size)
{
    t_list      *entity_item;
    t_entity    *entity;
    t_size      entity_size;
    double      scale;
    double      original_scale;
    t_coords    player_center;
    t_coords    entity_offset;

    original_scale = fmin((double)minimap_size.width / (double)game->map->size.width,
                (double)minimap_size.height / (double)game->map->size.height);
    scale = original_scale * game->minimap.zoom_level;
    entity_size = (t_size){scale, scale};
    player_center = (t_coords){
        game->player->billboard.entity.coords.x,
        game->player->billboard.entity.coords.y,
        0};
    entity_offset = (t_coords){
        (minimap_size.width / 2) - (player_center.x * scale),
        (minimap_size.height / 2) - (player_center.y * scale), 0};
    entity_item = game->entities;
    while (entity_item)
    {
        entity = entity_item->data;
        if (entity != (t_entity *)game->player)
            render_entity(canvas, game, entity, minimap_coords, minimap_size,
                    (t_coords){
                        minimap_coords.x + entity_offset.x,
                        minimap_coords.y + entity_offset.y, 0},
                    entity_size);
        entity_item = entity_item->next;
    }
    render_entity(canvas, game, (t_entity *)game->player, minimap_coords, minimap_size,
        (t_coords){
            minimap_coords.x + entity_offset.x,
            minimap_coords.y + entity_offset.y,0},
        entity_size);
}

void	render_minimap(t_game *game, t_ftm_image *canvas, t_coords coords, t_size size)
{
	ftm_draw_rectangle(canvas, coords, size, (t_ftm_rectangle){game->minimap.background_color, game->minimap.border_color, (t_size){1, 1}});
	render_entities(canvas, game, coords, size);
}
