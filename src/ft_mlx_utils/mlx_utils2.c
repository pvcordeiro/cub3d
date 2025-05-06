/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 17:05:31 by afpachec          #+#    #+#             */
/*   Updated: 2025/05/06 17:23:50 by afpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_mlx_utils.h>

unsigned int	*image_pixel(t_image *image, t_coords coords)
{
	if (coords.x < 0 || coords.y < 0 || coords.x > image->size.width || coords.y > image->size.height)
		return (NULL);
	return (image->data + (int)((coords.y * image->size_line)
		+ (coords.x * (image->bits_per_pixel / 8))));
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
