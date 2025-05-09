/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paude-so <paude-so@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 23:31:48 by afpachec          #+#    #+#             */
/*   Updated: 2025/05/09 21:39:23 by paude-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "player.h"

static void    player_looks(t_player *player)
{
    double rotation_speed;
    double old_dir_x;
    double old_plane_x;
    
    // Calculate rotation
    if (player->looking_left)
        rotation_speed = -player->key_look_sens * (PI / 180.0);
    else if (player->looking_right)
        rotation_speed = player->key_look_sens * (PI / 180.0);
    else
        return;
    
    // Rotate direction vector
    old_dir_x = player->dir.x;
    player->dir.x = player->dir.x * cos(rotation_speed) - player->dir.y * sin(rotation_speed);
    player->dir.y = old_dir_x * sin(rotation_speed) + player->dir.y * cos(rotation_speed);
    
    // Rotate camera plane
    old_plane_x = player->plane.x;
    player->plane.x = player->plane.x * cos(rotation_speed) - player->plane.y * sin(rotation_speed);
    player->plane.y = old_plane_x * sin(rotation_speed) + player->plane.y * cos(rotation_speed);
    
    // Update yaw for compatibility with other systems
    player->base.coords.yaw = ft_normalize_angle(atan2(player->dir.y, player->dir.x) * 180.0 / PI);
}

static bool	position_overlaps(t_list *entities, t_player *player, t_coords coords)
{
	t_list		*curr;
	t_entity	*curr_entity;

	curr = entities;
	while (curr)
	{
		curr_entity = curr->data;
        if (curr_entity != (t_entity *)player && curr_entity->hard
            && (int)(coords.x + PLAYER_HITBOX_RADIUS) >= (int)curr_entity->coords.x
            && (int)(coords.x - PLAYER_HITBOX_RADIUS) <= (int)(curr_entity->coords.x + 0.9)
            && (int)(coords.y + PLAYER_HITBOX_RADIUS) >= (int)curr_entity->coords.y
            && (int)(coords.y - PLAYER_HITBOX_RADIUS) <= (int)(curr_entity->coords.y + 0.9))
            return (true);
		curr = curr->next;
	}
	return (false);
}


static void    player_walk(t_list *entities, t_player *player, double dir_x, double dir_y)
{
    double    new_x;
    double    new_y;

    new_x = player->base.coords.x + PLAYER_SPEED * dir_x;
    if (!position_overlaps(entities, player, (t_coords){new_x, player->base.coords.y, 0, 0}))
        player->base.coords.x = new_x;

    new_y = player->base.coords.y + PLAYER_SPEED * dir_y;
    if (!position_overlaps(entities, player, (t_coords){player->base.coords.x, new_y, 0, 0}))
        player->base.coords.y = new_y;
}

static void    player_walks(t_list *entities, t_player *player)
{
    if (player->walking_forward)
        player_walk(entities, player, player->dir.x, player->dir.y);
    if (player->walking_backward)
        player_walk(entities, player, -player->dir.x, -player->dir.y);
    if (player->walking_right)
        player_walk(entities, player, player->plane.x, player->plane.y);
    if (player->walking_left)
        player_walk(entities, player, -player->plane.x, -player->plane.y);
}

static void player_rays(t_game *game, t_player *player)
{
    t_raycast raycast;
    size_t i;

    i = -1;
    while (++i < PLAYER_RAYS)
    {
        raycast = send_ray(game, player->base.coords, i);
        player->rays[i].direction_of_hit_on_entity = raycast.direction_of_hit_on_entity;
        player->rays[i].length = raycast.length;
        player->rays[i].hit_entity = raycast.hit_entity;
        player->rays[i].x_of_hit_in_entity = raycast.x_of_hit_in_entity;
        
        // Calculate the angle for compatibility with other parts of the code
        double camera_x = 2 * i / (double)PLAYER_RAYS - 1;
        double ray_dir_x = player->dir.x + player->plane.x * camera_x;
        double ray_dir_y = player->dir.y + player->plane.y * camera_x;
        player->rays[i].angle = ft_normalize_angle(atan2(ray_dir_y, ray_dir_x) * 180.0 / PI);
    }
}

static void	player_frame(t_entity *entity)
{
	player_looks((t_player *)entity);
	player_walks(cub3d()->game.entities, (t_player *)entity);
	player_rays(&cub3d()->game, (t_player *)entity);
}

static void	free_player(void *entity)
{
	free(entity);
}

t_player    *player_new(char direction)
{
    t_player    *player;

    player = ft_calloc(1, sizeof(t_player));
    if (!player)
        return (NULL);
    player->base.type = ENTITY_PLAYER;
    player->base.frame = player_frame;
    player->base.free = free_player;
    
    // Initialize direction vector and plane based on starting direction
    if (direction == 'N')
    {
        player->dir = (t_coords){0, -1, 0, 0}; // Pointing up
        player->plane = (t_coords){0.66, 0, 0, 0}; // FOV is about 66 degrees
        player->base.coords.yaw = 270.0; // Keep yaw for compatibility
    }
    else if (direction == 'S')
    {
        player->dir = (t_coords){0, 1, 0, 0}; // Pointing down
        player->plane = (t_coords){-0.66, 0, 0, 0};
        player->base.coords.yaw = 90.0;
    }
    else if (direction == 'E')
    {
        player->dir = (t_coords){1, 0, 0, 0}; // Pointing right
        player->plane = (t_coords){0, 0.66, 0, 0};
        player->base.coords.yaw = 0.0;
    }
    else if (direction == 'W')
    {
        player->dir = (t_coords){-1, 0, 0, 0}; // Pointing left
        player->plane = (t_coords){0, -0.66, 0, 0};
        player->base.coords.yaw = 180.0;
    }
    
    return (player);
}
