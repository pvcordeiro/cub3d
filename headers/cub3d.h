/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paude-so <paude-so@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 17:14:52 by afpachec          #+#    #+#             */
/*   Updated: 2025/05/03 20:12:26 by paude-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define PI 3.14159265359

# include <mlx.h>

# include <ft_error.h>
# include <ft_utils.h>

# include <X11/keysym.h>
# include <stdio.h>
# include <stdbool.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>

# ifndef W_TITLE
#  define W_TITLE "Wolfenstein"
# endif

# ifndef W_WIDTH
#  define W_WIDTH 1280
# endif

# ifndef W_HEIGHT
#  define W_HEIGHT 720
# endif

#ifndef MINIMAP_WIDTH
# define MINIMAP_WIDTH (W_WIDTH / 4)
#endif

# ifndef MINIMAP_HEIGHT
#  define MINIMAP_HEIGHT (W_HEIGHT / 4)
# endif

# define LINE_STEP 1024

# define PLAYER_SPEED 0.3
# define PLAYER_TURN_SPEED 6.0
# define PLAYER_FOV 72.0
# define PLAYER_RAYS 256
# define PLAYER_RAYS_MAX_LENGTH 100.0
# define MAP_CHARS "10NSEW"

typedef struct s_coords
{
	double	x;
	double	y;
	double	z;
	double	yaw;
}	t_coords;

typedef struct s_size
{
	int	width;
	int	height;
}	t_size;

typedef struct s_image
{
	char	*path;
	void	*img_ptr;
	int		bits_per_pixel;
	int		size_line;
	int		endian;
	void	*data;
	t_size	size;
}	t_image;

typedef struct s_window
{
	t_size	size;
	void	*win;
	void	*mlx;
	t_image	*canvas;
	bool	initialized;
}	t_window;

typedef struct s_sprite
{
	t_list	*images;
	size_t	index;
	t_time	updated_at;
	t_time	update_delay;
}	t_sprite;

typedef enum e_entity_type
{
	ENTITY_WALL,
	ENTITY_PLAYER
}	t_entity_type;

typedef struct s_entity
{
	bool			hard;
	t_coords		coords;
	t_entity_type	type;
	t_sprite		*sprite;
	void			(*frame)(struct s_entity *this);
	void			(*free)(void *this);
	void			*private;
}	t_entity;

typedef struct s_map
{
	t_entity	*player;
	t_list		*entities;
	char		*path;
	t_hashmap	*types;
	char		**raw;
	char		**map;
	t_size		size;
	bool		initialized;
}	t_map;

typedef struct s_ray
{
	double	length;
	double	angle;
}	t_ray;

typedef struct	s_player
{
	bool	walking_forward;
	bool	walking_left;
	bool	walking_backward;
	bool	walking_right;
	bool	looking_right;
	bool	looking_left;
	t_ray	rays[PLAYER_RAYS];
}	t_player;

typedef struct s_cub3d
{
	t_window	window;
	t_map		map;
}	t_cub3d;

// cub3d
t_cub3d	*cub3d(void);
void	cub3d_exit(int code);
int		cub3d_loop(void *_);
int		key_release_frame(int key_code);
int		key_press_frame(int key_code);

void	create_window_e(t_window *window, t_size size, char *title);
void	parse_map_e(t_map *map, int argc, char **argv);
void	destroy_map(t_map *map);
void	destroy_window(t_window *window);

// Images
void	free_image(t_image *image);
t_image	*image_from_file(char *path);
t_list	*images_from_files(char **file_paths);
t_image	*image_new(t_size size);

// Render
void	clear_canvas(t_image *canvas);

// Entities
void	call_entity_frames(t_list *entities);
void	render_map(t_map *map, t_image *canvas, t_coords coords, t_size size);
void	create_entities_e(t_map *map);

// Raycasting
void			render_raycasting_mega(t_map *map, t_image *canvas);

#endif
