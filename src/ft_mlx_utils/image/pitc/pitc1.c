/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pitc1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 00:39:42 by afpachec          #+#    #+#             */
/*   Updated: 2025/05/20 17:17:15 by afpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pitc.h"

unsigned int inline get_modified_pixel(unsigned int (*pm)(void *, unsigned int),
	void *data, unsigned int pixel)
{
	if (!pm)
		return (pixel);
	return (pm(data, pixel));
}


inline t_coords	get_src_coords(t_ftm_pitc_config pitc,
	t_size index, t_coords scale)
{
	return ((t_coords){pitc.crop_start.x + (int)(index.width
		* scale.x), pitc.crop_start.y + (int)(index.height * scale.y), 0});
}

inline t_coords	get_canvas_coords(t_ftm_pitc_config pitc, t_size index)
{
	return ((t_coords){pitc.coords.x + index.width, pitc.coords.y
		+ index.height, 0});
}

inline void	set_pixel(t_set_pixel_config set_pixel_config)
{
	unsigned int *canvas_pixel;
	unsigned int *image_pixel;

	canvas_pixel = ftm_image_pixel(set_pixel_config.canvas,
		get_canvas_coords(set_pixel_config.pitc, set_pixel_config.index));
	if (!canvas_pixel)
		return ;
	image_pixel = ftm_image_pixel(set_pixel_config.image,
		get_src_coords(set_pixel_config.pitc,
			set_pixel_config.index, set_pixel_config.scale));
	if (!image_pixel)
		return ;
	ftm_set_pixel(canvas_pixel,
		get_modified_pixel(set_pixel_config.pitc.pixel_modifier,
			set_pixel_config.pitc.pixel_modifier_data, *image_pixel));
}
