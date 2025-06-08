/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game8.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paude-so <paude-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 23:46:52 by afpachec          #+#    #+#             */
/*   Updated: 2025/06/08 20:40:54 by paude-so         ###   ########.fr       */
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

static int	count_sprite(t_hashmap *sprites, char *key)
{
	int		i;
	char	*full_key;
	void	*found;

	i = 1;
	while (1)
	{
		full_key = ft_strf("%s_%d", key, i);
		found = ft_hashmap_get_value(sprites, full_key);
		free(full_key);
		if (!found)
			break ;
		i++;
	}
	return (i - 1);
}

static void	fill_sprites(t_sprite **sprites, t_hashmap *game_sprites, char *key)
{
	int		angle;
	int		count;
	int		size;
	int		sprite_index;
	char	*full_key;
	int		offset;

	count = count_sprite(game_sprites, key);
	if (!count)
		return ;
	size = 360 / count;
	offset = size / 2;
	angle = -1;
	while (++angle <= 360)
	{
		sprite_index = (ft_normalize_angle(angle - offset)) / size + 1;
		if (sprite_index > count)
			sprite_index = 1;
		full_key = ft_strf("%s_%d", key, sprite_index);
		sprites[angle] = ft_hashmap_get_value(game_sprites, full_key);
		free(full_key);
	}
}
void	init_sprites_3d(t_game *game)
{
	t_element	*curr;
	t_element	*el;
	char		*key;
	int			len;
	int			i;
	char		*key_base;
	t_sprite	**sprites;

	el = *game->sprites->table;
	while (el)
	{
		curr = el;
		el = el->next;
		key = curr->key;
		len = ft_strlen(key);
		i = len - 1;

		// Vai para trás até achar onde termina o número no final
		while (i >= 0 && ft_isdigit(key[i]))
			i--;

		if (i < 1 || key[i] != '_')
			continue;

		// Copia a parte antes do "_<number>"
		key_base = ft_strndup(key, i);
		if (!key_base)
			continue;

		if (!ft_hashmap_get_value(game->sprites_3d, key_base))
		{
			sprites = ft_calloc(360, sizeof(t_sprite *));
			if (!sprites)
			{
				free(key_base);
				continue;
			}
			fill_sprites(sprites, game->sprites, key_base);
			ft_hashmap_set(game->sprites_3d, key_base, sprites, free);
		}
		free(key_base);
	}
}
