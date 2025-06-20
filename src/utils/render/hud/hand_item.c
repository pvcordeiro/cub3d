/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hand_item.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paude-so <paude-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 23:28:52 by afpachec          #+#    #+#             */
/*   Updated: 2025/06/20 17:35:22 by paude-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hud.h"

t_ftm_pitc_config	get_pitc_config(t_ftm_image *canvas, t_ftm_image *image)
{
	t_size	new_size;
	static double angle;

	angle += 1.0;
	if (angle > 360)
		angle = 0.0;
	new_size = (t_size){
		.width = (canvas->size.width / 1.5),
		.height = (canvas->size.height / 1.5) * ((double)image->size.width / image->size.height)
	};
	return ((t_ftm_pitc_config){
		.coords = (t_coords){(canvas->size.width / 2) - (new_size.width / 2),
			(canvas->size.height / 2) - (new_size.height / 2), 0},
		.crop = false,
		.resize = true,
		.size = new_size,
		.pixel_modifier = NULL
	});
}

static t_size	get_hand_item_size(t_ftm_image *canvas, t_size stats_size, t_ftm_image	*image)
{
	double		aspect_ratio;
	double		max_width;
	double		max_height;
	double		width_ratio;
	double		height_ratio;

	max_width = canvas->size.width;
	max_height = canvas->size.height - stats_size.height;
	aspect_ratio = (double)image->size.width / image->size.height;
	width_ratio = max_width / image->size.width;
	height_ratio = max_height / image->size.height;
	if (width_ratio < height_ratio)
	{
		display_size.width = max_width;
		display_size.height = max_width / aspect_ratio;
	}
	else
	{
		display_size.height = max_height;
		display_size.width = max_height * aspect_ratio;
	}
}

void	render_hand_item(t_ftm_image *canvas, t_character *character, t_size stats_size)
{
	t_item		*item;
	t_sprite	*sprite;
	t_ftm_image	*image;
	t_size		display_size;

	item = character->inventory[character->inventory_index];
	if (!item)
		return ;
	sprite = item->screen_sprite;
	if (!sprite)
		sprite = item->icon_sprite;
	image = get_sprite_image(sprite);
	double x_pos = (max_width - display_size.width) / 2;
	double y_pos = (max_height - display_size.height) / 2;
	ftm_put_image_to_canvas(canvas, image,
        (t_ftm_pitc_config){
        .coords = (t_coords){x_pos, y_pos, 0},
        .crop = false,
        .resize = true,
        .size = display_size,
        .pixel_modifier = NULL
    });
}
