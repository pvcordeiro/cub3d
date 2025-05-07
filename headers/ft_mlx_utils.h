/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mlx_utils.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 16:46:27 by afpachec          #+#    #+#             */
/*   Updated: 2025/05/07 23:47:38 by afpachec         ###   ########.fr       */
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

typedef struct s_ftm_image
{
	void	*display;
	char	*path;
	void	*img_ptr;
	int		bits_per_pixel;
	int		size_line;
	int		endian;
	void	*data;
	t_size	size;
}	t_ftm_image;

typedef struct s_ftm_window
{
	t_size	size;
	void	*win;
	void	*display;
	t_ftm_image	*canvas;
}	t_ftm_window;

typedef struct	s_ftm_pitc_config
{
	t_coords 	coords;
	bool		crop;
	t_coords	crop_start;
	t_coords	crop_end;
	bool		resize;
	t_size 		size;
	void		*pixel_modifier_data;
	unsigned	(*pixel_modifier)(void *data, unsigned pixel);
}	t_ftm_pitc_config;

void			ftm_free_image(void *image);
t_ftm_image		*ftm_image_from_file(t_ftm_window *window, char *path);
t_ftm_image		*ftm_image_new(t_ftm_window *window, t_size size);
t_list			*ftm_images_from_files(t_ftm_window *window, char **file_paths);

void			ftm_image_clean(t_ftm_image *image);
void			ftm_put_image_to_canvas(t_ftm_image *canvas, t_ftm_image *image, t_ftm_pitc_config pitc);

void			ftm_clear_window(void *window);
void			ftm_free_window(void *window);
void			ftm_create_window_e(t_ftm_window *window, t_size size, char *title);
void			ftm_update_window(t_ftm_window *window);

unsigned int	*ftm_image_pixel(t_ftm_image *image, t_coords coords);
void			ftm_set_pixel(unsigned *pixel, unsigned value);

void			ftm_draw_line(t_ftm_image *canvas, t_coords start, t_coords end, unsigned color);
void			ftm_draw_line_angle(t_ftm_image *canvas, t_coords start, double angle, double length, unsigned color);
void			ftm_draw_rectangle(t_ftm_image *canvas, t_coords coords, t_size size, unsigned color, unsigned border_color);


#endif