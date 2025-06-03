/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game8.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 23:46:52 by afpachec          #+#    #+#             */
/*   Updated: 2025/06/03 00:43:48 by afpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

static void process_door_at(t_game *game, int y, int x, t_sprite *frame_sprite)
{
	t_door	*door;

	if (!frame_sprite)
		return ;
	door = (t_door *)game->walls[y][x];
	if (door->direction == NORTH || door->direction == SOUTH)
	{
		((t_wall *)game->walls[y][x - 1])->east_sprite = frame_sprite;
		((t_wall *)game->walls[y][x + 1])->west_sprite = frame_sprite;
	}
	else if (door->direction == EAST || door->direction == WEST)
	{
		((t_wall *)game->walls[y - 1][x])->south_sprite = frame_sprite;
		((t_wall *)game->walls[y + 1][x])->north_sprite = frame_sprite;
	}
}

void insert_door_frames(t_game *game)
{
    int y, x;

    y = -1;
    while (++y < game->map->size.height)
    {
        x = -1;
        while (++x < game->map->size.width)
        {
            if (game->walls[y][x] && game->walls[y][x]->type == ENTITY_DOOR)
				process_door_at(game, y, x,
					((t_door *)game->walls[y][x])->door_sides_sprite);
        }
    }
}
