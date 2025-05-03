/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paude-so <paude-so@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 22:31:49 by afpachec          #+#    #+#             */
/*   Updated: 2025/05/03 19:23:15 by paude-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

#include <cub3d.h>

unsigned int	*get_pixel(t_image *image, t_coords coords);
void			render_image_to_canvas(t_image *canvas, t_image *image, t_coords coords);
void			put_pixel_in_image(t_image *image, t_coords coords, unsigned int pixel);
void			draw_line(t_image *canvas, t_coords start, t_coords end, unsigned int color);
void			draw_line_angle(t_image *canvas, t_coords start, double angle, double length, unsigned int color);
void			draw_rectangle(t_image *canvas, t_coords coords, t_size size, unsigned int color, unsigned int border_color);

#endif