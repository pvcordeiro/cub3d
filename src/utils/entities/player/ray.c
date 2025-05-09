/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paude-so <paude-so@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 12:05:46 by paude-so          #+#    #+#             */
/*   Updated: 2025/05/09 21:42:50 by paude-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "player.h"





t_raycast send_ray(t_game *game, t_coords coords, int ray_index)
{
    t_player *player = game->player;
    t_dda_ray data = {0};
    t_wall *wall_hit;
    double camera_x;
    
    // Calculate ray position and direction
    camera_x = 2 * ray_index / (double)PLAYER_RAYS - 1; // x-coordinate in camera space
    data.ray_dir.x = player->dir.x + player->plane.x * camera_x;
    data.ray_dir.y = player->dir.y + player->plane.y * camera_x;
    
    // Initialize DDA parameters
    data.map_pos.x = (int)coords.x;
    data.map_pos.y = (int)coords.y;
    
    // Calculate delta distance
    if (data.ray_dir.x == 0)
        data.delta_dist.x = 1e30;
    else
        data.delta_dist.x = fabs(1 / data.ray_dir.x);
    
    if (data.ray_dir.y == 0)
        data.delta_dist.y = 1e30;
    else
        data.delta_dist.y = fabs(1 / data.ray_dir.y);
    
    // Calculate step and initial side distance
    if (data.ray_dir.x < 0)
    {
        data.step.x = -1;
        data.side_dist.x = (coords.x - data.map_pos.x) * data.delta_dist.x;
    }
    else
    {
        data.step.x = 1;
        data.side_dist.x = (data.map_pos.x + 1.0 - coords.x) * data.delta_dist.x;
    }
    
    if (data.ray_dir.y < 0)
    {
        data.step.y = -1;
        data.side_dist.y = (coords.y - data.map_pos.y) * data.delta_dist.y;
    }
    else
    {
        data.step.y = 1;
        data.side_dist.y = (data.map_pos.y + 1.0 - coords.y) * data.delta_dist.y;
    }
    
    // Perform DDA algorithm
    while (1)
    {
        if (data.side_dist.x < data.side_dist.y)
        {
            data.side_dist.x += data.delta_dist.x;
            data.map_pos.x += data.step.x;
            data.side = 0;
        }
        else
        {
            data.side_dist.y += data.delta_dist.y;
            data.map_pos.y += data.step.y;
            data.side = 1;
        }
        
        // Check if ray hit a wall
        if (data.map_pos.x < 0 || data.map_pos.x >= game->map->size.width ||
            data.map_pos.y < 0 || data.map_pos.y >= game->map->size.height)
            return ((t_raycast){PLAYER_RAYS_NO_HIT_LENGTH, NULL, 0, 0});
        
        wall_hit = game->wall_grid[(int)data.map_pos.y][(int)data.map_pos.x];
        if (wall_hit)
            break;
    }
    
    // Calculate distance projected on camera direction
    if (data.side == 0)
    {
        data.length = (data.map_pos.x - coords.x + (1 - data.step.x) / 2) / data.ray_dir.x;
        data.direction_of_hit_on_entity = (data.step.x > 0) ? WEST : EAST;
    }
    else
    {
        data.length = (data.map_pos.y - coords.y + (1 - data.step.y) / 2) / data.ray_dir.y;
        data.direction_of_hit_on_entity = (data.step.y > 0) ? NORTH : SOUTH;
    }

    // Calculate perpendicular wall distance to avoid fisheye effect
    double perp_wall_dist;
    if (data.side == 0)
        perp_wall_dist = (data.map_pos.x - coords.x + (1 - data.step.x) / 2) / data.ray_dir.x;
    else
        perp_wall_dist = (data.map_pos.y - coords.y + (1 - data.step.y) / 2) / data.ray_dir.y;
    
    // Calculate where exactly the wall was hit
    if (data.side == 0)
        data.wall_x = coords.y + data.length * data.ray_dir.y;
    else
        data.wall_x = coords.x + data.length * data.ray_dir.x;
    data.wall_x -= floor(data.wall_x);
    
    return ((t_raycast){perp_wall_dist, (t_entity *)wall_hit, data.wall_x, data.direction_of_hit_on_entity});
}
