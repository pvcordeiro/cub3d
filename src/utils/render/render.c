/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paude-so <paude-so@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 16:50:17 by afpachec          #+#    #+#             */
/*   Updated: 2025/05/03 18:31:52 by paude-so         ###   ########.fr       */
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

void	draw_line(t_image *canvas, t_coords start, t_coords end, unsigned int color)
{
	double	dx;
	double	dy;
	double	step;
	double	x;
	double	y;
	int		i;

	dx = end.x - start.x;
	dy = end.y - start.y;
	step = LINE_STEP;
	dx /= step;
	dy /= step;
	x = start.x;
	y = start.y;
	i = 0;
	while (i <= step)
	{
		put_pixel_in_image(canvas, (t_coords){(int)x, (int)y, 0, 0}, color);
		x += dx;
		y += dy;
		i++;
	}
}

void	draw_line_angle(t_image *canvas, t_coords start, double angle, double length, unsigned int color)
{
	static t_coords	end;

	angle = ft_normalize_angle(angle - 90);
    end.x = start.x + cos(angle * PI / 180.0) * length;
    end.y = start.y + sin(angle * PI / 180.0) * length;
	draw_line(canvas, start, end, color);
}
