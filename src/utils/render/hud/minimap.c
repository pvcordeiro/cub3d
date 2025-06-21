/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 17:48:25 by paude-so          #+#    #+#             */
/*   Updated: 2025/06/21 01:42:26 by afpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hud.h"

static void	set_entity_color(t_minimap_data mp_data, t_entity *entity, unsigned *color)
{
	if (entity->type == ENTITY_WALL)
		*color = mp_data.game->hud.minimap.wall_color;
	else if (entity->type == ENTITY_PLAYER)
		*color = mp_data.game->hud.minimap.player_color;
	else if (entity->type == ENTITY_DOOR)
		*color = mp_data.game->hud.minimap.door_color;
	else
		*color = mp_data.game->hud.minimap.entity_color;
}

static bool in_boundaries(t_minimap_data mp_data, t_coords entity_pos)
{
    return (entity_pos.x + mp_data.size.width * 0.2>= mp_data.coords.x &&
            entity_pos.y + mp_data.size.height * 0.2 >= mp_data.coords.y &&
            entity_pos.x - mp_data.size.width * 0.2 < mp_data.coords.x + mp_data.size.width &&
            entity_pos.y - mp_data.size.height * 0.2 < mp_data.coords.y + mp_data.size.height);
}

static void fix_clipping(t_minimap_data mp_data, t_coords *pos, t_size *size)
{
	int	clip_left;
	int	clip_right;
	int	clip_top;
	int	clip_bottom;
	
	clip_left = mp_data.coords.x - pos->x;
	clip_right = (pos->x + size->width) - (mp_data.coords.x + mp_data.size.width);
	clip_top = mp_data.coords.y - pos->y;
	clip_bottom = (pos->y + size->height) - (mp_data.coords.y + mp_data.size.height);
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

static void	render_entity(t_minimap_data mp_data, t_entity *entity, t_coords coords, t_size entity_size)
{
	unsigned int	color;
	t_coords		new_coords;
    t_size          draw_size;

	new_coords = (t_coords){(int)(coords.x + (entity->coords.x * entity_size.width)), (int)(coords.y + (entity->coords.y * entity_size.height)), entity->coords.yaw};
    if (!in_boundaries(mp_data, new_coords))
        return ;
    set_entity_color(mp_data, entity, &color);
	if (entity == (t_entity *)mp_data.character)
	{
		ftm_draw_arrow(mp_data.canvas,
				new_coords,
				(t_size){entity_size.width / 1.5, entity_size.height / 1.5},
				color);
		return ;
	}
    draw_size = (t_size){entity_size.width * entity->size.width,
    entity_size.height * entity->size.height};
    fix_clipping(mp_data, &new_coords, &draw_size);
	ftm_draw_rectangle(mp_data.canvas,
			new_coords,
			draw_size,
			(t_ftm_rectangle){color, color, (t_size){1, 1}});
}

static void render_entities(t_minimap_data mp_data)
{
    t_list      *entity_item;
    t_entity    *entity;
    t_size      entity_size;
    double      scale;
    double      original_scale;
    t_coords    player_center;
    t_coords    entity_offset;

    original_scale = fmin((double)mp_data.size.width / (double)mp_data.game->map->size.width,
                (double)mp_data.size.height / (double)mp_data.game->map->size.height);
    scale = original_scale * mp_data.game->hud.minimap.zoom_level;
    entity_size = (t_size){scale, scale};
    player_center = (t_coords){
        mp_data.character->billboard.entity.coords.x,
        mp_data.character->billboard.entity.coords.y,
        0};
    entity_offset = (t_coords){
        (mp_data.size.width / 2) - (player_center.x * scale),
        (mp_data.size.height / 2) - (player_center.y * scale), 0};
    entity_item = mp_data.game->entities;
    while (entity_item)
    {
        entity = entity_item->data;
        if (entity != (t_entity *)mp_data.character && entity->active)
            render_entity(mp_data, entity,
                    (t_coords){
                        mp_data.coords.x + entity_offset.x,
                        mp_data.coords.y + entity_offset.y, 0},
                    entity_size);
        entity_item = entity_item->next;
    }
    render_entity(mp_data, (t_entity *)mp_data.character,
        (t_coords){
            mp_data.coords.x + entity_offset.x,
            mp_data.coords.y + entity_offset.y,0},
        entity_size);
}

static void	render_minimapp(t_minimap_data mp_data)
{
	ftm_draw_rectangle(mp_data.canvas, mp_data.coords, mp_data.size,
		(t_ftm_rectangle){mp_data.game->hud.minimap.background_color,
			mp_data.game->hud.minimap.border_color, (t_size){1, 1}});
	render_entities(mp_data);
}

void	render_minimap(t_game *game, t_ftm_image *canvas, t_character *character)
{
	t_minimap_data	mp_data;

	mp_data = (t_minimap_data){game, canvas, character, (t_coords){0, 0, 0}, canvas->size};
	if (!game->hud.minimap.full)
	{
		mp_data.size = (t_size){canvas->size.width * MINIMAP_WIDTH_MULTIPLIER, canvas->size.height * MINIMAP_HEIGHT_MULTIPLIER};
		mp_data.coords = (t_coords){canvas->size.width - mp_data.size.width - 10, 10, 0};
	}
	render_minimapp(mp_data);
}
