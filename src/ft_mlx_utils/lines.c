/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lines.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 17:37:16 by afpachec          #+#    #+#             */
/*   Updated: 2025/05/07 23:15:58 by afpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_mlx_utils.h>

void	ftm_draw_line(t_ftm_image *canvas, t_coords start, t_coords end, unsigned color)
{
	double	dx;
	double	dy;
	double	step;
	double	x;
	double	y;
	int		i;

	dx = end.x - start.x;
	dy = end.y - start.y;
	step = FT_MLX_UTILS_DRAW_LINE_STEP;
	dx /= step;
	dy /= step;
	x = start.x;
	y = start.y;
	i = 0;
	while (i <= step)
	{
		ftm_set_pixel(ftm_image_pixel(canvas, (t_coords){x, y, 0, 0}), color);
		x += dx;
		y += dy;
		i++;
	}
}

void	ftm_draw_line_angle(t_ftm_image *canvas, t_coords start, double angle, double length, unsigned color)
{
	static t_coords	end;

	angle = ft_normalize_angle(angle);
    end.x = start.x + cos(angle * FT_MLX_UTILS_PI / 180.0) * length;
    end.y = start.y + sin(angle * FT_MLX_UTILS_PI / 180.0) * length;
	ftm_draw_line(canvas, start, end, color);
}

void	ftm_draw_rectangle(t_ftm_image *canvas, t_coords coords, t_size size, unsigned color, unsigned border_color)
{
	int			i;
	int			j;
	unsigned	tmp_color;

	i = -1;
	while (++i < size.width)
	{
		j = -1;
		while (++j < size.height)
		{
			tmp_color = color;
			if (i == 0 || i == size.width - 1 || j == 0 || j == size.height - 1)
				tmp_color = border_color;
			ftm_set_pixel(ftm_image_pixel(canvas, (t_coords){coords.x + i, coords.y + j, 0, 0}), tmp_color);
		}
	}
}
