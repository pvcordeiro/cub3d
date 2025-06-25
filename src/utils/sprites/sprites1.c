/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 19:01:44 by afpachec          #+#    #+#             */
/*   Updated: 2025/06/25 20:12:30 by afpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

t_ftm_image	*get_sprite_image(t_sprite *sprite)
{
	t_list	*curr_image_node;
	ssize_t	new_index;
	t_time	update_diference;
	ssize_t	count;

	if (!sprite)
		return (get_sprite_image(&cub3d()->placeholder));
	update_diference = ft_get_time() - sprite->updated_at;
	if (sprite->update_delay && sprite->running
		&& update_diference > sprite->update_delay)
	{
		int delta = (int)(update_diference / sprite->update_delay);
		count = (ssize_t)ft_list_size(sprite->images);
		if (sprite->reversed)
			new_index = sprite->index - delta;
		else
			new_index = sprite->index + delta;
		if (sprite->loop)
			new_index = ((new_index % count) + count) % count;
		else if (new_index < 0 || new_index >= count)
		{
			sprite->running = false;
			new_index = (count - 1) * (new_index >= count);
		}
		sprite->index = new_index;
		sprite->updated_at = ft_get_time();
	}
	curr_image_node = ft_list_index(sprite->images, sprite->index);
	if (!curr_image_node)
		return (NULL);
	return (curr_image_node->data);
}

t_ftm_image	*get_sprite3d_image(t_sprite **sprite3d, double angle)
{
	return (get_sprite_image(sprite3d[(int)ft_normalize_angle(angle)]));
}
