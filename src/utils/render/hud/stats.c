/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stats.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 22:14:35 by afpachec          #+#    #+#             */
/*   Updated: 2025/06/20 18:02:13 by afpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hud.h"

void	render_ammo_text(t_game *game, t_ftm_image *canvas, t_character *character, t_size stats_size)
{
	t_coords	text_pos;
	char		*ammo_text;
	double		ammo_scaler;

	if (character->ammo > 999)
		ammo_text = ft_strdup("999");
	else
		ammo_text = ft_strf("%d", character->ammo);
	ammo_scaler = 1.47;
	if (ft_strlen(ammo_text) == 3)
		ammo_scaler = 1.50;
	if (ft_strlen(ammo_text) == 2)
		ammo_scaler = 1.48;
	text_pos = (t_coords){stats_size.width / ammo_scaler,
		canvas->size.height - stats_size.height * 0.5, 0};
	ftm_draw_text(canvas, game->hud.stats_font,
		(t_ftm_text_config){
			.text = ammo_text,
			.coords = text_pos,
			.height = stats_size.width * 0.04,
			.spacing = 4,
			.color = 0xCFFFFFFF
		});
	free(ammo_text);
}

void	render_health_text(t_game *game, t_ftm_image *canvas, t_character *character, t_size stats_size)
{
	t_coords			text_pos;
	char				*health_text;
	double				health_scaler;

	health_text = ft_strf("%d%%", character->billboard.entity.health);
	health_scaler = 1.88;
	if (ft_strlen(health_text) == 3)
		health_scaler = 1.81;
	if (ft_strlen(health_text) == 2)
		health_scaler = 1.78;
	text_pos = (t_coords){stats_size.width / health_scaler,
		canvas->size.height - stats_size.height * 0.5, 0};
	ftm_draw_text(canvas, game->hud.stats_font,
		(t_ftm_text_config){
			.text = health_text,
			.coords = text_pos,
			.height = stats_size.width * 0.04,
			.spacing = 4,
			.color = 0xCFFFFFFF
		});
	free(health_text);
}

static t_size	get_hand_item_size(t_ftm_image *image, double max_w, double max_h)
{
    t_size		item_size;
    double		aspect_ratio;

    aspect_ratio = (double)image->size.width / image->size.height;
    if (aspect_ratio > 1.0)
    {
        item_size.width = max_w;
        item_size.height = max_w / aspect_ratio;
        if (item_size.height > max_h)
        {
            item_size.height = max_h;
            item_size.width = max_h * aspect_ratio;
        }
		return (item_size);
    }
	item_size.height = max_h;
	item_size.width = max_h * aspect_ratio;
	if (item_size.width > max_w)
	{
		item_size.width = max_w;
		item_size.height = max_w / aspect_ratio;
	}
	return (item_size);
}

void	render_hand_item_icon(t_ftm_image *canvas, t_character *character, t_size stats_size)
{
    t_item		*item;
    t_ftm_image	*image;
    t_size		item_size;

    item = character->inventory[character->inventory_index];
    if (!item)
        return ;
    image = get_sprite_image(item->icon_sprite);
	item_size = get_hand_item_size(image, stats_size.width * 0.15, stats_size.height * 0.5);
    ftm_put_image_to_canvas(canvas, image,
        (t_ftm_pitc_config){
        .coords = (t_coords){(stats_size.width * 0.87) - (item_size.width / 2),
            (canvas->size.height - stats_size.height * 0.5) - (item_size.height / 2), 0},
        .crop = false,
        .resize = true,
        .size = item_size,
        .pixel_modifier = NULL
    });
}

t_size	render_stats(t_game *game, t_ftm_image *canvas, t_character *character)
{
	t_size		stats_size;
	t_ftm_image	*image;
	int			index;

	if (!game->hud.stats_enabled || !game->hud.stats.states)
		return ((t_size){0, 0});
	stats_size = (t_size){canvas->size.width, canvas->size.width / 8};
	index = (int)(game->hud.stats.states
			* ((float)character->billboard.entity.health
				/ character->billboard.entity.max_health));
	index = game->hud.stats.states - index;
	if (index >= game->hud.stats.states)
		index = game->hud.stats.states - 1;
	if (index < 0)
		index = 0;
	image = get_sprite_image(ft_list_index(game->hud.stats.states_list,
				index)->data);
	ftm_put_image_to_canvas(canvas, image,
		(t_ftm_pitc_config){
		(t_coords){0, canvas->size.height - stats_size.height, 0},
		false, (t_coords){0, 0, 0}, (t_coords){0, 0, 0},
		true, stats_size, NULL, NULL});
	render_health_text(game, canvas, character, stats_size);
	render_ammo_text(game, canvas, character, stats_size);
	render_hand_item_icon(canvas, character, stats_size);
	return (stats_size);
}
