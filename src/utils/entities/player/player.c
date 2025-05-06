/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 23:31:48 by afpachec          #+#    #+#             */
/*   Updated: 2025/05/05 21:49:44 by afpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "player.h"

static void	player_looks(t_entity *entity, t_player *player)
{
	if (player->looking_left)
		entity->coords.yaw -= PLAYER_TURN_SPEED;
	else if (player->looking_right)
		entity->coords.yaw += PLAYER_TURN_SPEED;
	entity->coords.yaw = ft_normalize_angle(entity->coords.yaw);
}

static bool	position_overlaps(t_entity *entity, t_coords coords)
{
	t_list		*curr;
	t_entity	*curr_entity;

	curr = cub3d()->map.entities;
	while (curr)
	{
		curr_entity = curr->data;
		if (curr_entity != entity && curr_entity->hard
			&& (int)curr_entity->coords.x == (int)coords.x
			&& (int)curr_entity->coords.y == (int)coords.y)
			return (true);
		curr = curr->next;
	}
	return (false);
}

static void	update_entity_grid(t_entity *entity, int old_x, int old_y,
		int new_x, int new_y)
{
	t_map	*map;

	map = &cub3d()->map;
	if (old_x >= 0 && old_x < map->size.width && old_y >= 0
		&& old_y < map->size.height)
		map->entity_grid[old_y][old_x] = NULL;
	if (new_x >= 0 && new_x < map->size.width && new_y >= 0
		&& new_y < map->size.height)
		map->entity_grid[new_y][new_x] = entity;
}

static void	move_player_x(t_entity *entity, double angle_radians)
{
	double	new_x;
	int		old_x;
	int		grid_x;

	old_x = (int)entity->coords.x;
	new_x = entity->coords.x + PLAYER_SPEED * cos(angle_radians);
	grid_x = (int)new_x;
	if (!position_overlaps(entity, (t_coords){new_x, entity->coords.y, 0, 0}))
	{
		entity->coords.x = new_x;
		if (grid_x != old_x && entity->hard)
			update_entity_grid(entity, old_x, (int)entity->coords.y, grid_x,
				(int)entity->coords.y);
	}
}

static void	move_player_y(t_entity *entity, double angle_radians)
{
	double	new_y;
	int		old_y;
	int		grid_y;

	old_y = (int)entity->coords.y;
	new_y = entity->coords.y + PLAYER_SPEED * sin(angle_radians);
	grid_y = (int)new_y;
	if (!position_overlaps(entity, (t_coords){entity->coords.x, new_y, 0, 0}))
	{
		entity->coords.y = new_y;
		if (grid_y != old_y && entity->hard)
			update_entity_grid(entity, (int)entity->coords.x, old_y,
				(int)entity->coords.x, grid_y);
	}
}

static void	player_walk(t_entity *entity, double angle)
{
	double	angle_radians;

	angle_radians = ft_normalize_angle(angle) * (PI / 180.0);
	move_player_x(entity, angle_radians);
	move_player_y(entity, angle_radians);
}

static void	player_walks(t_entity *entity, t_player *player)
{
	if (player->walking_backward)
		player_walk(entity, entity->coords.yaw - 180.0);
	if (player->walking_right)
		player_walk(entity, entity->coords.yaw + 90.0);
	if (player->walking_left)
		player_walk(entity, entity->coords.yaw - 90.0);
	if (player->walking_forward)
		player_walk(entity, entity->coords.yaw);
}

static void	player_rays(t_map *map, t_entity *entity)
{
	t_player	*player;
	t_coords	ray_coords;
	t_raycast	raycast;
	size_t		i;
	double		angle;

	(void)map;
	player = entity->private;
	i = -1;
	angle = entity->coords.yaw - PLAYER_FOV / 2;
	ray_coords = entity->coords;
	while (++i < PLAYER_RAYS)
	{
		ray_coords.yaw = ft_normalize_angle(angle + ((PLAYER_FOV / PLAYER_RAYS)
					* i));
		raycast = send_ray(map, entity, ray_coords);
		player->rays[i].direction_of_hit_on_entity = raycast.direction_of_hit_on_entity;
		player->rays[i].length = raycast.length;
		player->rays[i].hit_entity = raycast.hit_entity;
		player->rays[i].x_of_hit_in_entity = raycast.x_of_hit_in_entity;
		player->rays[i].angle = ray_coords.yaw;
	}
}

static void	player_frame(t_entity *entity)
{
	t_player	*player;
	t_map		*map;

	map = &cub3d()->map;
	player = (t_player *)(entity->private);
	player_looks(entity, player);
	player_walks(entity, player);
	player_rays(map, entity);
}

static void	free_player(void *entity)
{
	free(((t_entity *)entity)->private);
	free(entity);
}

t_entity	*entity_player_new(char direction)
{
	t_entity	*entity;
	t_player	*player;

	player = ft_calloc(1, sizeof(t_player));
	if (!player)
		return (NULL);
	entity = entity_new(ENTITY_PLAYER, player);
	if (!entity)
		return (free(player), NULL);
	entity->frame = player_frame;
	entity->free = free_player;
	if (direction == 'W')
		entity->coords.yaw = 180.0;
	else if (direction == 'S')
		entity->coords.yaw = 0.0;
	else if (direction == 'N')
		entity->coords.yaw = 270.0;
	else if (direction == 'E')
		entity->coords.yaw = 90.0;
	return (entity);
}
