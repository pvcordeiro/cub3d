/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   missing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 17:31:41 by afpachec          #+#    #+#             */
/*   Updated: 2025/05/05 17:32:12 by afpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sprites.h"

t_list	*get_missing_images(void)
{
	t_list	*list;
	t_image	*image;

	list = NULL;
	image = image_from_file(MISSING_IMAGE_PATH);
	if (image)
		ft_list_add(&list, image, (void (*)(void *))free_image);
	return (list);
}
