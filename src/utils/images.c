/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   images.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paude-so <paude-so@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 18:51:44 by afpachec          #+#    #+#             */
/*   Updated: 2025/05/04 16:03:39 by paude-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	free_image(void *image)
{
	mlx_destroy_image(cub3d()->window.mlx, ((t_image *)image)->img_ptr);
	free(image);
}

static bool	load_image_addresses(t_image *image)
{
	image->data = mlx_get_data_addr(image->img_ptr, &image->bits_per_pixel, &image->size_line, &image->endian);
	return (!!image->data);
}

t_image	*image_from_file(char *path)
{
	t_image *image;

	image = ft_calloc(1, sizeof(t_image));
	if (!image)
		return (NULL);
	image->img_ptr = mlx_xpm_file_to_image(cub3d()->window.mlx, path, &image->size.width, &image->size.height);
	if (!image->img_ptr)
		return (free(image), NULL);
	if (!load_image_addresses(image))	
		return (free_image(image), NULL);
	return (image);
}

t_image	*image_new(t_size size)
{
	t_image *image;

	image = ft_calloc(1, sizeof(t_image));
	if (!image)
		return (NULL);
	image->img_ptr = mlx_new_image(cub3d()->window.mlx, size.width, size.height);
	if (!image->img_ptr)
		return (free(image), NULL);
	image->size = size;
	if (!load_image_addresses(image))	
		return (free_image(image), NULL);
	return (image);
}

t_list	*images_from_files(char **file_paths)
{
	size_t	i;
	t_list	*list;
	t_image	*tmp_image;

	list = NULL;
	i = -1;
	while (file_paths[++i])
	{
		tmp_image = image_from_file(file_paths[i]);
		if (!tmp_image)
			return (ft_list_destroy(&list), NULL);
		ft_list_add(&list, tmp_image, (void (*)(void *))free_image);
	}
	return (list);
}
