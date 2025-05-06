/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 22:31:49 by afpachec          #+#    #+#             */
/*   Updated: 2025/05/06 17:06:51 by afpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

#include <cub3d.h>

typedef struct	s_render_cropped_image_config
{
	t_coords 	coords;
	t_coords	crop_start;
	t_coords	crop_end;
	t_size 		size;
	void		*pixel_modifier_data;
	unsigned	(*pixel_modifier)(void *data, unsigned pixel);
}	t_render_cropped_image_config;

void			render_cropped_image_to_canvas(t_image *canvas, t_image *image, t_render_cropped_image_config rcic);
void			put_pixel_in_image(t_image *image, t_coords coords, unsigned int pixel);
void			draw_line(t_image *canvas, t_coords start, t_coords end, unsigned int color);
void			draw_line_angle(t_image *canvas, t_coords start, double angle, double length, unsigned int color);
void			draw_rectangle(t_image *canvas, t_coords coords, t_size size, unsigned int color, unsigned int border_color);

#endif