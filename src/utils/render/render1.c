/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 16:50:17 by afpachec          #+#    #+#             */
/*   Updated: 2025/05/06 12:25:23 by afpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

unsigned int	*get_pixel(t_image *image, t_coords coords)
{
	return (image->data + (int)((coords.y * image->size_line)
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
			if (src_coords.x >= 0 && src_coords.x < image->size.width &&
				src_coords.y >= 0 && src_coords.y < image->size.height)
			{
				put_pixel_in_image(canvas,
					(t_coords){rcic.coords.x + i, rcic.coords.y + j, 0, 0},
					rcic.pixel_modifier(rcic.pixel_modifier_data, *get_pixel(image, src_coords)));
			}
		}
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
	step = DRAW_LINE_STEP;
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

	angle = ft_normalize_angle(angle);
    end.x = start.x + cos(angle * PI / 180.0) * length;
    end.y = start.y + sin(angle * PI / 180.0) * length;
	draw_line(canvas, start, end, color);
}

void	draw_rectangle(t_image *canvas, t_coords coords, t_size size, unsigned int color, unsigned int border_color)
{
	int				i;
	int				j;
	unsigned int	tmp_color;

	i = -1;
	while (++i < size.width)
	{
		j = -1;
		while (++j < size.height)
		{
			tmp_color = color;
			if (i == 0 || i == size.width - 1 || j == 0 || j == size.height - 1)
				tmp_color = border_color;
			put_pixel_in_image(canvas, (t_coords){coords.x + i, coords.y + j, 0, 0}, tmp_color);
		}
	}
}

void	clear_canvas(t_image *canvas)
{
	draw_rectangle(canvas, (t_coords){0, 0, 0 ,0}, (t_size){W_WIDTH, W_HEIGHT}, 0x000000, 0x000000);
}
