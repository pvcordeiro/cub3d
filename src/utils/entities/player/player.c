/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 23:31:48 by afpachec          #+#    #+#             */
/*   Updated: 2025/05/07 23:00:17 by afpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "player.h"

static void	player_looks(t_player *player)
{
	if (player->looking_left)
		player->base.coords.yaw -= PLAYER_TURN_SPEED;
	else if (player->looking_right)
		player->base.coords.yaw += PLAYER_TURN_SPEED;
	player->base.coords.yaw = ft_normalize_angle(player->base.coords.yaw);
}

static bool	position_overlaps(t_player *player, t_coords coords)
{
	t_list		*curr;
	t_entity	*curr_entity;

	curr = cub3d()->game.entities;
	while (curr)
	{
		curr_entity = curr->data;
		if (curr_entity != (t_entity *)player && curr_entity->hard
			&& (int)curr_entity->coords.x == (int)coords.x
			&& (int)curr_entity->coords.y == (int)coords.y)
			return (true);
		curr = curr->next;
	}
	return (false);
}

static void	update_entity_grid(t_game *game, t_player *player, t_coords old_coords, t_coords new_coords)
{
	if ((int)old_coords.x >= 0 && (int)old_coords.x < game->map->size.width && (int)old_coords.y >= 0
		&& (int)old_coords.y < game->map->size.height)
		game->entity_grid[(int)old_coords.y][(int)old_coords.x] = NULL;
	if ((int)new_coords.x >= 0 && (int)new_coords.x < game->map->size.width && (int)new_coords.y >= 0
		&& (int)new_coords.y < game->map->size.height)
		game->entity_grid[(int)new_coords.y][(int)new_coords.x] = (t_entity *)player;
}

static void	move_player_x(t_game *game, t_player *player, double angle_radians)
{
	double	new_x;
	int		old_x;
	int		grid_x;

	old_x = (int)player->base.coords.x;
	new_x = player->base.coords.x + PLAYER_SPEED * cos(angle_radians);
	grid_x = (int)new_x;
	if (!position_overlaps(player, (t_coords){new_x, player->base.coords.y, 0, 0}))
	{
		player->base.coords.x = new_x;
		if (grid_x != old_x && player->base.hard)
			update_entity_grid(game, player, (t_coords){old_x, player->base.coords.y, 0, 0}, (t_coords){grid_x, player->base.coords.y, 0, 0});
	}
}

static void	move_player_y(t_game *game, t_player *player, double angle_radians)
{
	double	new_y;
	int		old_y;
	int		grid_y;

	old_y = (int)player->base.coords.y;
	new_y = player->base.coords.y + PLAYER_SPEED * sin(angle_radians);
	grid_y = (int)new_y;
	if (!position_overlaps(player, (t_coords){player->base.coords.x, new_y, 0, 0}))
	{
		player->base.coords.y = new_y;
		if (grid_y != old_y && player->base.hard)
			update_entity_grid(game, player, (t_coords){player->base.coords.x, old_y, 0, 0}, (t_coords){player->base.coords.x, grid_y, 0, 0});
	}
}

static void	player_walk(t_game *game, t_player *player, double angle)
{
	double	angle_radians;

	angle_radians = ft_normalize_angle(angle) * (PI / 180.0);
	move_player_x(game, player, angle_radians);
	move_player_y(game, player, angle_radians);
}

static void	player_walks(t_game *game, t_player *player)
{
	if (player->walking_backward)
		player_walk(game, player, player->base.coords.yaw - 180.0);
	if (player->walking_right)
		player_walk(game, player, player->base.coords.yaw + 90.0);
	if (player->walking_left)
		player_walk(game, player, player->base.coords.yaw - 90.0);
	if (player->walking_forward)
		player_walk(game, player, player->base.coords.yaw);
}

static void	player_rays(t_game *game, t_player *player)
{
	t_coords	ray_coords;
	t_raycast	raycast;
	size_t		i;
	double		angle;

	i = -1;
	angle = player->base.coords.yaw - PLAYER_FOV / 2;
	ray_coords = player->base.coords;
	while (++i < PLAYER_RAYS)
	{
		ray_coords.yaw = ft_normalize_angle(angle + ((PLAYER_FOV / PLAYER_RAYS)
					* i));
		raycast = send_ray(game, player, ray_coords);
		player->rays[i].direction_of_hit_on_entity = raycast.direction_of_hit_on_entity;
		player->rays[i].length = raycast.length;
		player->rays[i].hit_entity = raycast.hit_entity;
		player->rays[i].x_of_hit_in_entity = raycast.x_of_hit_in_entity;
		player->rays[i].angle = ray_coords.yaw;
	}
}

static void	player_frame(t_entity *entity)
{
	player_looks((t_player *)entity);
	player_walks(&cub3d()->game, (t_player *)entity);
	player_rays(&cub3d()->game, (t_player *)entity);
}

static void	free_player(void *entity)
{
	free(entity);
}

t_player	*player_new(char direction)
{
	t_player	*player;

	player = ft_calloc(1, sizeof(t_player));
	if (!player)
		return (NULL);
	player->base.type = ENTITY_PLAYER;
	player->base.frame = player_frame;
	player->base.free = free_player;
	if (direction == 'W')
		player->base.coords.yaw = 180.0;
	else if (direction == 'S')
		player->base.coords.yaw = 0.0;
	else if (direction == 'N')
		player->base.coords.yaw = 270.0;
	else if (direction == 'E')
		player->base.coords.yaw = 90.0;
	return (player);
}
