/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 17:05:31 by afpachec          #+#    #+#             */
/*   Updated: 2025/05/06 17:06:00 by afpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_mlx_utils.h>

unsigned int	*image_pixel(t_image *image, t_coords coords)
{
	return (image->data + (int)((coords.y * image->size_line)
		+ (coords.x * (image->bits_per_pixel / 8))));
}
