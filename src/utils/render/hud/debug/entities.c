/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entities.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 02:07:13 by afpachec          #+#    #+#             */
/*   Updated: 2025/05/20 02:08:43 by afpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debug.h"

void	set_entities(t_game *game)
{
	static t_time	last_check;

	if (ft_get_time() - last_check < 1000)
		return ;
	free(game->hud.debug.entities);
	game->hud.debug.entities = ft_strf("Entities: %d", ft_list_size(game->entities));
}
