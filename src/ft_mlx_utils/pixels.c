/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixels.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 17:05:31 by afpachec          #+#    #+#             */
/*   Updated: 2025/05/06 22:53:27 by afpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_mlx_utils.h>

unsigned int	*ftm_image_pixel(t_image *image, t_coords coords)
{
	int	x;
	int	y;

	x = coords.x;
	y = coords.y;
	if (x < 0 || y < 0 || x > image->size.width || y > image->size.height)
		return (NULL);
	return (image->data + (y * image->size_line) + (x * (image->bits_per_pixel / 8)));
}

unsigned blend_pixel(unsigned dst, unsigned src)
{
	// If alpha is missing (top byte zero), assume fully opaque
	unsigned alpha = (src >> 24) & 0xFF;
	if (alpha == 0 && (src & 0xFFFFFF) != 0)
		alpha = 255;

	if (alpha == 255)
		return src;
	if (alpha == 0)
		return dst;

	// Continue as normal
	unsigned src_r = (src >> 16) & 0xFF;
	unsigned src_g = (src >> 8) & 0xFF;
	unsigned src_b = src & 0xFF;

	unsigned dst_r = (dst >> 16) & 0xFF;
	unsigned dst_g = (dst >> 8) & 0xFF;
	unsigned dst_b = dst & 0xFF;

	unsigned out_r = (src_r * alpha + dst_r * (255 - alpha)) / 255;
	unsigned out_g = (src_g * alpha + dst_g * (255 - alpha)) / 255;
	unsigned out_b = (src_b * alpha + dst_b * (255 - alpha)) / 255;

	return (0xFF << 24) | (out_r << 16) | (out_g << 8) | out_b;
}

void	ftm_set_pixel(unsigned *pixel, unsigned value)
{
	if (!pixel)
		return ;
	*pixel = blend_pixel(*pixel, value);
}
