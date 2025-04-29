/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 17:14:52 by afpachec          #+#    #+#             */
/*   Updated: 2025/04/29 10:29:53 by afpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <mlx.h>

# include <ft_error.h>
# include <ft_utils.h>

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

# define PLAYER_SPEED 0.5
# define PLAYER_TURN_SPEED 10.0
# define MAP_CHARS "10NSEW"

typedef struct s_window
{
	int		height;
	int		width;
	void	*win;
	void	*mlx;
	bool	initialized;
}	t_window;

typedef struct s_map
{
	char		*path;
	t_hashmap	*types;
	char		**raw;
	char		**map;
	bool		initialized;
}	t_map;

typedef struct s_image
{
	char	*path;
	void	*img_ptr;
	int		*bits_per_pixel;
	int		*size_line;
	int		*endian;
	int		width;
	int		height;
}	t_image;

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
	double			x;
	double			y;
	double			z;
	double			yaw;
	t_entity_type	type;
	t_sprite		*sprite;
	void			(*frame)(struct s_entity *this);
	void			*private;
}	t_entity;

typedef struct	s_player
{
	bool	walking_forward;
	bool	walking_left;
	bool	walking_backward;
	bool	walking_right;
	bool	looking_right;
	bool	looking_left;
}	t_player;

typedef struct s_cub3d
{
	t_window	window;
	t_map		map;
	t_list		entities;
}	t_cub3d;

t_cub3d	*cub3d(void);
void	cub3d_exit(int code);
void	create_window_e(t_window *window, int width, int height, char *title);
void	parse_map_e(t_map *map, int argc, char **argv);
void	destroy_map(t_map *map);
void	destroy_window(t_window *window);

// Images
void	free_image(void *_image);
t_image	*image_from_file(char *path);
t_list	*images_from_files(char **file_paths);

#endif
