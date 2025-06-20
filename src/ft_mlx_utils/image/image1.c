/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 14:51:11 by afpachec          #+#    #+#             */
/*   Updated: 2025/06/20 18:11:37 by afpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "image.h"

void	ftm_image_clear(t_ftm_image *image)
{
	ftm_draw_rectangle(image, (t_coords){0, 0, 0},
		image->size, (t_ftm_rectangle){0, 0, (t_size){0, 0}});
}

char	*ftm_image_to_str(t_ftm_image *image)
{
	if (!image)
		return (NULL);
	return (ft_strf("Image<path: \"%s\", size: {width: %d, height: %d}>", 
		image->path, image->size.width, image->size.height));
}

void	ftm_put_image_to_window(t_ftm_window *window, t_ftm_image *image,
	t_coords coords)
{
	if (!image || !image->img_ptr)
		return ;
	mlx_put_image_to_window(window->display, window->win,
		image->img_ptr, coords.x, coords.y);
}
