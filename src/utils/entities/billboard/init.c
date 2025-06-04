/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paude-so <paude-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 00:50:48 by afpachec          #+#    #+#             */
/*   Updated: 2025/06/04 18:42:55 by paude-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "billboard.h"

static	int count_sprite(t_hashmap *sprites, char identifier)
{
	int		i;
	char	*keykeykey;
	void	*pagman;

	i = 1;
	while (true)
	{
		keykeykey = ft_strf("%d_SPRITE", i);
		pagman = hashmap_get_with_identifier(sprites, identifier, keykeykey);
		free(keykeykey);
		if (!pagman)
			break ;
		++i;
	}
	return (i - 1);
}

static void	fill_sprites(t_billboard *billboard, t_hashmap *game_sprites, char identifier)
{
    int		angle;
    int		count;
    int		size;
    int		sprite_index;
	char	*keykeykey;
    int		offset;

    count = count_sprite(game_sprites, identifier);
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
		keykeykey = ft_strf("%d_SPRITE", sprite_index);
        billboard->sprites[angle] = hashmap_get_with_identifier(
            game_sprites, identifier, keykeykey);
		free(keykeykey);
    }
}

void	init_billboard(t_game *game, t_ftm_window *window, t_billboard *billboard, char identifier)
{
	int	i;

	i = -1;
	init_entity(game, window, (t_entity *)billboard, identifier);
	billboard->entity.type = ENTITY_BILLBOARD;
	billboard->entity.frame = billboard_frame;
	billboard->entity.clear = clear_billboard;
	billboard->entity.action = billboard_action;
	billboard->entity.shot = billboard_shot;
	billboard->entity.billboard = true;
	billboard->entity.size = (t_dsize){BILLBOARD_WIDTH, BILLBOARD_HEIGHT};
	if (hashmap_get_with_identifier(game->sprites, billboard->entity.identifier, "SPRITE"))
	{
		while (++i < 360)
			billboard->sprites[i] = hashmap_get_with_identifier(game->sprites, billboard->entity.identifier, "SPRITE");
		return ;
	}
	fill_sprites(billboard, game->sprites, billboard->entity.identifier);
}


t_billboard	*billboard_new(t_game *game, t_ftm_window *window, char identifier)
{
	t_billboard	*billboard;

	billboard = ft_calloc(1, sizeof(t_billboard));
	if (!billboard)
		return (NULL);
	init_billboard(game, window, billboard, identifier);
	return (billboard);
}
