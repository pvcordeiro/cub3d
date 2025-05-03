/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paude-so <paude-so@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 22:31:49 by afpachec          #+#    #+#             */
/*   Updated: 2025/05/03 12:48:21 by paude-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

#include <cub3d.h>

unsigned int	*get_pixel(t_image *image, t_coords coords);
void			render_image_to_canvas(t_image *canvas, t_image *image, t_coords coords);
void			put_pixel_in_image(t_image *image, t_coords coords, unsigned int pixel);
void			draw_line(t_image *canvas, t_coords start, t_coords end, unsigned int color);

#endif