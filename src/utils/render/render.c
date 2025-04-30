/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 16:50:17 by afpachec          #+#    #+#             */
/*   Updated: 2025/04/30 00:03:28 by afpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

unsigned int	*get_pixel(t_image *image, t_coords coords)
{
	return (image->data + (int)round((coords.y * image->size_line)
		+ (coords.x * (image->bits_per_pixel / 8))));
}

static bool	valid_position_inside_image(t_image *image, t_coords coords)
{
	int	x;
	int	y;

	x = coords.x;
	y = coords.y;
	return (x >= 0 && x < image->size.width && y >= 0 && y < image->size.height);
}

static bool	is_transparent_pixel(unsigned int pixel)
{
	return (pixel == 0xFF000000);
}

void	put_pixel_in_image(t_image *image, t_coords coords, unsigned int pixel)
{
	if (is_transparent_pixel(pixel) || !valid_position_inside_image(image, coords))
		return ;
	*get_pixel(image, coords) = pixel;
}

void	render_image_to_canvas(t_image *canvas, t_image *image, t_coords coords)
{
	int				i;
	int				j;

	i = -1;
	while (++i < image->size.width)
	{
		j = -1;
		while (++j < image->size.height)
			put_pixel_in_image(canvas, (t_coords){coords.x + i, coords.y + j, 0, 0},
				*get_pixel(image, (t_coords){i, j, 0, 0}));
	}
}
