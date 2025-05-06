/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mlx_utils.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 16:46:27 by afpachec          #+#    #+#             */
/*   Updated: 2025/05/06 17:41:46 by afpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MLX_UTILS_H
# define FT_MLX_UTILS_H

# define FT_MLX_UTILS_PI 3.14159265359

// External Libs
# include <mlx.h>

// Internal Libs
# include <ft_utils.h>
# include <ft_error.h>

// Line drawing step size (Used for diagonal lines)
# define FT_MLX_UTILS_DRAW_LINE_STEP 1024

typedef struct s_image
{
	void	*display;
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
	void	*display;
	t_image	*canvas;
	bool	initialized;
}	t_window;

void			free_image(void *image);
t_image			*image_from_file(t_window *window, char *path);
t_image			*image_new(t_window *window, t_size size);
t_list			*images_from_files(t_window *window, char **file_paths);

void			free_window(void *window);
void			create_window_e(t_window *window, t_size size, char *title);
void			update_window(t_window *window);

unsigned int	*image_pixel(t_image *image, t_coords coords);
void			set_pixel(unsigned *pixel, unsigned value);

void			draw_line(t_image *canvas, t_coords start, t_coords end, unsigned color);
void			draw_line_angle(t_image *canvas, t_coords start, double angle, double length, unsigned color);
void			draw_rectangle(t_image *canvas, t_coords coords, t_size size, unsigned color, unsigned border_color);


#endif