/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 17:14:52 by afpachec          #+#    #+#             */
/*   Updated: 2025/05/07 23:04:31 by afpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define PI 3.14159265359

// MLX
# include <mlx.h>

// Internal Libs
# include <ft_error.h>
# include <ft_utils.h>
# include <ft_mlx_utils.h>

// External Libs
# include <X11/keysym.h>
# include <stdio.h>
# include <stdbool.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>

// Window Config
# define W_TITLE "Wolfenstein"
# define W_WIDTH 1024
# define W_HEIGHT 768

// Default minimap size multipliers
# define MINIMAP_WIDTH_MULTIPLIER 0.25
# define MINIMAP_HEIGHT_MULTIPLIER 0.25

// Placeholder Image
# define PLACEHOLDER_IMAGE_PATH "assets/placeholder.xpm"
# define PLACEHOLDER_SPRITE_UPDATE_DELAY 0

// Player Config
# define PLAYER_SPEED 0.15
# define PLAYER_TURN_SPEED 3.0
# define PLAYER_RAYS_NO_HIT_LENGTH 100.0
# define PLAYER_FOV 75.0
# define PLAYER_RAYS 1024

// Map Config
# define MAP_CHARS "10NSEW"

typedef struct s_sprite
{
	t_list			*images;
	size_t			index;
	t_time			updated_at;
	t_time			update_delay;
}	t_sprite;

typedef enum e_entity_type
{
	ENTITY_PLAYER,
	ENTITY_WALL,
}	t_entity_type;

typedef struct s_entity
{
	void			(*frame)(struct s_entity *this);
	void			(*free)(void *this);
	bool			transparent;
	bool			hard;
	t_coords		coords;
	t_entity_type	type;
}	t_entity;

typedef struct s_ray
{
	double		length;
	double		angle;
	t_entity	*hit_entity;
	t_direction	direction_of_hit_on_entity;
	double		x_of_hit_in_entity;
	int			_height;
}	t_ray;

typedef struct	s_player
{
	t_entity	base;
	bool		walking_forward;
	bool		walking_left;
	bool		walking_backward;
	bool		walking_right;
	bool		looking_right;
	bool		looking_left;
	t_ray		rays[PLAYER_RAYS];
}	t_player;

typedef struct	s_wall
{
	t_entity	base;
	t_sprite	*north_sprite;
	t_sprite	*south_sprite;
	t_sprite	*west_sprite;
	t_sprite	*east_sprite;
	double		north_depth;
	double		south_depth;
	double		west_depth;
	double		east_depth;
}	t_wall;

typedef struct s_map
{
	char		*path;
	t_hashmap	*types;
	char		**raw;
	char		**map;
	t_size		size;
}	t_map;

typedef struct	s_environment
{
	unsigned	floor_color;
	unsigned	ceiling_color;
}	t_environment;

typedef struct	s_minimap
{
	t_coords	coords;
	t_size		size;
	bool		full;
	double		width_multiplier;
	double		height_multiplier;
	unsigned	background_color;
	unsigned	border_color;
	unsigned	entity_color;
	unsigned	wall_color;
	unsigned	player_color;
	unsigned	player_ray_color;
}	t_minimap;

typedef struct	s_game
{
	t_environment		environment;
	t_minimap			minimap;
	t_map				*map;
	t_player			*player;
	t_list				*entities;
	t_entity			***entity_grid;
	t_hashmap			*sprites;
}	t_game;

typedef struct s_cub3d
{
	t_sprite			placeholder;
	t_map				*curr_map;
	t_window			window;
	bool				map_fullscreen;
	t_game				game;
}	t_cub3d;

void	game_load_map_e(t_game *game, t_window *window, t_map *map);
void	clear_game(void *game);
void	free_game(void *game);
void	render_game(t_window *window, t_game *game);
void	free_sprite(void *data);
void	clear_sprite(void *data);
void	init_sprite(t_sprite *sprite, t_list *images, t_time update_delay);
t_sprite	*sprite_new(t_list *images, t_time update_delay);

// cub3d
t_cub3d	*cub3d(void);
void	cub3d_exit(int code);

t_map	*parse_map_e(char *path);
void	destroy_map(t_map *map);

// Loop
int	loop(void *_);
int	key_up_handler(int key);
int	key_down_handler(int key);

// Render
void	render_ceiling_and_floor(t_game *game, t_image *canvas);

// Entities
void		call_entity_frames(t_list *entities);
void		create_entities_e(t_game *game);
t_sprite	*get_entity_sprite(t_entity *entity, t_direction direction);

// Raycasting
void			render_raycasting_mega(t_game *game, t_image *canvas);

// Sprites
t_image	*get_sprite_image(t_sprite *sprite);

#endif
