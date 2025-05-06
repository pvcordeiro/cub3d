/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 16:50:17 by afpachec          #+#    #+#             */
/*   Updated: 2025/05/06 17:48:14 by afpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

void	render_cropped_image_to_canvas(t_image *canvas, t_image *image, t_render_cropped_image_config rcic)
{
	int				i;
	int				j;
	t_coords		src_coords;
	double			x_scale;
	double			y_scale;
	int				crop_width;
	int				crop_height;

	crop_width = rcic.crop_end.x - rcic.crop_start.x;
	crop_height = rcic.crop_end.y - rcic.crop_start.y;
	if (crop_width <= 0 || crop_height <= 0 || rcic.size.width <= 0 || rcic.size.height <= 0)
		return;
	x_scale = (double)crop_width / rcic.size.width;
	y_scale = (double)crop_height / rcic.size.height;
	i = -1;
	while (++i < rcic.size.width)
	{
		j = -1;
		while (++j < rcic.size.height)
		{
			src_coords.x = rcic.crop_start.x + (int)(i * x_scale);
			src_coords.y = rcic.crop_start.y + (int)(j * y_scale);
			if (!ftm_image_pixel(image, src_coords))
				continue ;
			ftm_set_pixel(
				ftm_image_pixel(canvas, (t_coords){rcic.coords.x + i, rcic.coords.y + j, 0, 0}),
				rcic.pixel_modifier(rcic.pixel_modifier_data, *ftm_image_pixel(image, src_coords))
			);
		}
	}
}
