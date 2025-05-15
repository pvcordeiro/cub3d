/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 17:48:02 by afpachec          #+#    #+#             */
/*   Updated: 2025/05/15 19:16:53 by afpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "image.h"

static inline t_size	get_crop_size(t_ftm_image *image,
	t_ftm_pitc_config pitc)
{
	if (pitc.crop)
		return ((t_size){pitc.crop_end.x - pitc.crop_start.x,
			pitc.crop_end.y - pitc.crop_start.y});
	return (image->size);
}

static inline void	set_size(t_ftm_image *image, t_ftm_pitc_config *pitc)
{
	if (pitc->resize)
		return ;
	pitc->size = image->size;
}

static inline bool	is_under_zero(t_size a, t_size b)
{
	return (a.width <= 0 || a.height <= 0 || b.width <= 0 || b.height <= 0);
}

static inline t_coords	get_scale(t_size a, t_size b)
{
	return ((t_coords){(double)a.width / b.width,
		(double)a.height / b.height, 0, 0});
}

void	ftm_put_image_to_canvas(t_ftm_image *canvas, t_ftm_image *image,
	t_ftm_pitc_config pitc)
{
	t_size			index;
	t_coords		src_coords;
	t_coords		scale;
	t_size			cs;

	cs = get_crop_size(image, pitc);
	if (set_size(image, &pitc), is_under_zero(cs, pitc.size))
		return ;
	scale = get_scale(cs, pitc.size);
	index.width = -1;
	while (++index.width < pitc.size.width)
	{
		index.height = -1;
		while (++index.height < pitc.size.height)
		{
			src_coords = (t_coords){pitc.crop_start.x
				+ (int)(index.width * scale.x), pitc.crop_start.y
				+ (int)(index.height * scale.y), 0, 0};
			if (ftm_image_pixel(image, src_coords))
				ftm_set_pixel(ftm_image_pixel(canvas, (t_coords){pitc.coords.x
						+ index.width, pitc.coords.y + index.height, 0, 0}),
					get_modified_pixel(pitc.pixel_modifier, pitc.pixel_modifier_data,
						*ftm_image_pixel(image, src_coords)));
		}
	}
}
