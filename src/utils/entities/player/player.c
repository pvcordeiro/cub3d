/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 23:31:48 by afpachec          #+#    #+#             */
/*   Updated: 2025/05/19 22:52:17 by afpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "player.h"

static void	player_looks(t_player *player)
{
	if (player->looking_left)
		player->base.coords.yaw = ft_normalize_angle(player->base.coords.yaw - player->key_look_velocity);
	else if (player->looking_right)
		player->base.coords.yaw = ft_normalize_angle(player->base.coords.yaw + player->key_look_velocity);
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
            && coords.x + PLAYER_HITBOX_RADIUS >= curr_entity->coords.x
            && coords.x - PLAYER_HITBOX_RADIUS <= (curr_entity->coords.x + curr_entity->size.width)
            && coords.y + PLAYER_HITBOX_RADIUS >= curr_entity->coords.y
            && coords.y - PLAYER_HITBOX_RADIUS <= (curr_entity->coords.y + curr_entity->size.height))
            return (true);
		curr = curr->next;
	}
	return (false);
}

static void	move_player_x(t_list *entities, t_player *player, double angle_radians, double velocity)
{
	double	new_x;

	new_x = player->base.coords.x + velocity * cos(angle_radians);
	if (!position_overlaps(entities, player, (t_coords){new_x, player->base.coords.y, 0}))
		player->base.coords.x = new_x;
}

static void	move_player_y(t_list *entities, t_player *player, double angle_radians, double velocity)
{
	double	new_y;

	new_y = player->base.coords.y + velocity * sin(angle_radians);
	if (!position_overlaps(entities, player, (t_coords){player->base.coords.x, new_y, 0}))
		player->base.coords.y = new_y;
}

static void	player_walk(t_list *entities, t_player *player, double angle)
{
	double	angle_radians;
	double	velocity;

	velocity = player->walk_velocity;
	if (player->sprinting)
		velocity = player->sprint_velocity;
	angle_radians = ft_normalize_angle(angle) * (PI / 180.0);
	move_player_x(entities, player, angle_radians, velocity);
	move_player_y(entities, player, angle_radians, velocity);
}

static void	player_walks(t_list *entities, t_player *player)
{
	if (player->walking_backward)
		player_walk(entities, player, player->base.coords.yaw - 180.0);
	if (player->walking_right)
		player_walk(entities, player, player->base.coords.yaw + 90.0);
	if (player->walking_left)
		player_walk(entities, player, player->base.coords.yaw - 90.0);
	if (player->walking_forward)
		player_walk(entities, player, player->base.coords.yaw);
}

typedef struct s_rays_slice
{
	int			starting_index;
	int			ending_index;
	double		angle;
	t_coords	player_coords;
	t_game		*game;
	t_player	*player;
}	t_rays_slice;

static void	send_rays(void *data)
{
	t_raycast		raycast;
	t_coords		ray_coords;
	t_rays_slice	*rays_slice;
	int				i;
	int				j;
	bool			already_hit_non_transparent;
	t_entity		*entity_to_ignore;
	t_direction		direction_to_ignore;

	rays_slice = data;
	i = rays_slice->starting_index - 1;
	ray_coords = rays_slice->player_coords;
	while (++i < rays_slice->ending_index)
	{
		already_hit_non_transparent = false;
		ray_coords.yaw = ft_normalize_angle(rays_slice->angle + ((PLAYER_FOV / PLAYER_RAYS)
			* i));
		entity_to_ignore = (t_entity *)rays_slice->player;
		direction_to_ignore = NORTH;
		j = -1;
		while (++j < PLAYER_RAY_SUBRAYS)
		{
			if (already_hit_non_transparent)
			{
				rays_slice->player->rays[i][j].hit_entity = NULL;
				continue ;
			}
			raycast = send_ray(rays_slice->game, ray_coords, entity_to_ignore, direction_to_ignore);
			rays_slice->player->rays[i][j].direction_of_hit_on_entity = raycast.direction_of_hit_on_entity;
			rays_slice->player->rays[i][j].length = raycast.length;
			rays_slice->player->rays[i][j].hit_entity = raycast.hit_entity;
			rays_slice->player->rays[i][j].x_of_hit_in_entity = raycast.x_of_hit_in_entity;
			rays_slice->player->rays[i][j].angle = ray_coords.yaw;
			entity_to_ignore = rays_slice->player->rays[i][j].hit_entity;
			direction_to_ignore = rays_slice->player->rays[i][j].direction_of_hit_on_entity;
			if (rays_slice->player->rays[i][j].hit_entity && !rays_slice->player->rays[i][j].hit_entity->transparent)
				already_hit_non_transparent = true;
		}
	}	
}

static void	player_rays(t_game *game, t_player *player)
{
	static t_rays_slice	rays_slices[RAYCASTING_THREADS];
	int					i;

	i = -1;
	while (++i < RAYCASTING_THREADS)
	{
		rays_slices[i].starting_index = (PLAYER_RAYS / RAYCASTING_THREADS) * i;
		rays_slices[i].ending_index = (PLAYER_RAYS / RAYCASTING_THREADS) * (i + 1);
		rays_slices[i].angle = player->base.coords.yaw - (PLAYER_FOV / 2);
		rays_slices[i].player_coords = player->base.coords;
		rays_slices[i].game = game;
		rays_slices[i].player = player;
		game->raycasting_threads[i]->routine = send_rays;
		game->raycasting_threads[i]->data = &rays_slices[i];
		ftt_thread_run(game->raycasting_threads[i]);
	}
	i = -1;
	while (++i < RAYCASTING_THREADS)
		ftt_thread_wait(game->raycasting_threads[i]);
	player->target_entity = player->rays[PLAYER_RAYS / 2][0].hit_entity;
	player->target_entity_direction = player->rays[PLAYER_RAYS / 2][0].direction_of_hit_on_entity;
}

static void	player_mouse_moviment(t_player *player)
{
	if (!player->mouse_moviment)
		return ;
	player->base.coords.yaw = ft_normalize_angle(player->base.coords.yaw + (player->mouse_moviment * player->mouse_look_velocity));
}

static void	player_actions(t_player *player)
{
	if (player->action && player->already_actioned)
		return ;
	player->already_actioned = player->action;
	if (player->action && player->target_entity
		&& player->target_entity->action)
		player->target_entity->action(player->target_entity, (t_entity *)player);
}

static void	player_frame(t_entity *entity)
{
	player_looks((t_player *)entity);
	player_mouse_moviment((t_player *)entity);
	player_walks(cub3d()->game.entities, (t_player *)entity);
	player_rays(&cub3d()->game, (t_player *)entity);
	player_actions((t_player *)entity);
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
	player->key_look_velocity = PLAYER_KEY_LOOK_VELOCITY;
	player->mouse_look_velocity = PLAYER_MOUSE_LOOK_VELOCITY;
	player->walk_velocity = PLAYER_WALK_VELOCITY;
	player->sprint_velocity = PLAYER_SPRINT_VELOCITY;
	if (direction == 'N')
		player->base.coords.yaw = 270.0;
	else if (direction == 'S')
		player->base.coords.yaw = 90.0;
	else if (direction == 'W')
		player->base.coords.yaw = 180.0;
	return (player);
}
