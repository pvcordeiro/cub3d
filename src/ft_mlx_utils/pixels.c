/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixels.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 17:05:31 by afpachec          #+#    #+#             */
/*   Updated: 2025/05/06 17:36:43 by afpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_mlx_utils.h>

unsigned int	*image_pixel(t_image *image, t_coords coords)
{
	int	x;
	int	y;

	x = coords.x;
	y = coords.y;
	if (x < 0 || y < 0 || x > image->size.width || y > image->size.height)
		return (NULL);
	return (image->data + (y * image->size_line) + (x * (image->bits_per_pixel / 8)));
}

static inline bool	is_transparent_value(unsigned int value)
{
	return (value == 0xFF000000);
}

void	set_pixel(unsigned *pixel, unsigned value)
{
	if (pixel && !is_transparent_value(value))
		*pixel = value;
}
