/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   placeholder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 17:31:41 by afpachec          #+#    #+#             */
/*   Updated: 2025/05/06 16:55:45 by afpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sprites.h"

void	load_placeholder_sprite_e(t_window *window, t_sprite *placeholder)
{
	t_list	*list;
	t_image	*image;

	ft_error(ERROR_NO_ERROR);
	list = NULL;
	image = image_from_file(window, PLACEHOLDER_IMAGE_PATH);
	if (!image)
		return (ft_error(ERROR_LOAD_PLACEHOLDER_SPRITE));
	ft_list_add(&list, image, (void (*)(void *))free_image);
	init_sprite(placeholder, list, PLACEHOLDER_SPRITE_UPDATE_DELAY);
}
