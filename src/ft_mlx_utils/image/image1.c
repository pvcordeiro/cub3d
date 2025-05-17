/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 14:51:11 by afpachec          #+#    #+#             */
/*   Updated: 2025/05/18 00:41:16 by afpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "image.h"

void	ftm_image_clear(t_ftm_image *image)
{
	ftm_draw_rectangle(image, (t_coords){0, 0, 0, 0},
		image->size, (t_ftm_rectangle){0, 0, (t_size){0, 0}});
}

char	*ftm_image_to_str(t_ftm_image *image)
{
	if (!image)
		return (NULL);
	return (ft_strf("Image<path: \"%s\", size: {width: %d, height: %d}>", 
		image->path, image->size.width, image->size.height));
}

void	ftm_image_remove_transparency(t_ftm_image *image)
{
	int	i;
	int	j;

	i = -1;
	while (++i < image->size.width)
	{
		j = -1;
		while (++j < image->size.height)
			ftm_set_pixel(ftm_image_pixel(image, (t_coords){i, j, 0, 0}),
				ftm_remove_pixel_transparency(*ftm_image_pixel(image, (t_coords){i, j, 0, 0})));
	}
}
