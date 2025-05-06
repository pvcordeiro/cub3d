/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 17:29:32 by afpachec          #+#    #+#             */
/*   Updated: 2025/05/06 12:17:51 by afpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPRITES_H
# define SPRITES_H

#include <cub3d.h>

t_list	*get_missing_images(void);
void	load_placeholder_sprite_e(t_sprite *placeholder);
void	init_sprite(t_sprite *sprite, t_list *images, t_time update_delay);
void	free_sprite(void *data);

#endif