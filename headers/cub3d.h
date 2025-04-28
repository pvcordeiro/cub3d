/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 17:14:52 by afpachec          #+#    #+#             */
/*   Updated: 2025/04/28 15:52:30 by afpachec         ###   ########.fr       */
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

# ifndef W_TITLE
#  define W_TITLE "Wolfenstein"
# endif

# ifndef W_WIDTH
#  define W_WIDTH 1280
# endif

# ifndef W_HEIGHT
#  define W_HEIGHT 720
# endif

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
	int			height;
	int			width;
	char		*path;
	t_hashmap	*types;
	char		**raw;
	char		**map;
	bool		initialized;
}	t_map;

typedef struct s_cub3d
{
	t_window	window;
	t_map		map;
}	t_cub3d;

t_cub3d	*cub3d(void);
void	cub3d_exit(int code);
void	create_window_e(t_window *window, int width, int height, char *title);
void	parse_map_e(t_map *map, int argc, char **argv);
void	destroy_map(t_map *map);
void	destroy_window(t_window *window);

#endif
