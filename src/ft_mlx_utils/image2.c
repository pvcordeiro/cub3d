/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 17:48:02 by afpachec          #+#    #+#             */
/*   Updated: 2025/05/06 19:40:04 by afpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_mlx_utils.h>

void	ftm_image_clear(t_image *image)
{
	ftm_draw_rectangle(image, (t_coords){0, 0, 0 ,0}, image->size, 0, 0);
}

static inline t_size	get_crop_size(t_image *image, t_ftm_pitc_config pitc)
{
	if (pitc.crop)
		return ((t_size){pitc.crop_end.x - pitc.crop_start.x, pitc.crop_end.y - pitc.crop_start.y});
	return (image->size);
}

static inline void	set_size(t_image *image, t_ftm_pitc_config *pitc)
{
	if (pitc->resize)
		return ;
	pitc->size = image->size;
}

void	ftm_put_image_to_canvas(t_image *canvas, t_image *image, t_ftm_pitc_config pitc)
{
	t_size			index;
	t_coords		src_coords;
	t_coords		scale;
	t_size			crop_size;

	crop_size = get_crop_size(image, pitc);
	set_size(image, &pitc);
	if (crop_size.width <= 0 || crop_size.height <= 0 || pitc.size.width <= 0 || pitc.size.height <= 0)
		return;
	scale = (t_coords){(double)crop_size.width / pitc.size.width, (double)crop_size.height / pitc.size.height, 0, 0};
	index.width = -1;
	while (++index.width < pitc.size.width)
	{
		index.height = -1;
		while (++index.height < pitc.size.height)
		{
			src_coords = (t_coords){pitc.crop_start.x + (int)(index.width * scale.x), pitc.crop_start.y + (int)(index.height * scale.y), 0, 0};
			if (ftm_image_pixel(image, src_coords))
				ftm_set_pixel(
					ftm_image_pixel(canvas, (t_coords){pitc.coords.x + index.width, pitc.coords.y + index.height, 0, 0}),
					pitc.pixel_modifier(pitc.pixel_modifier_data, *ftm_image_pixel(image, src_coords))
				);
		}
	}
}
