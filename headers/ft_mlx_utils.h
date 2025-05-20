/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mlx_utils.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 16:46:27 by afpachec          #+#    #+#             */
/*   Updated: 2025/05/20 01:07:45 by afpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MLX_UTILS_H
# define FT_MLX_UTILS_H

# define FT_MLX_UTILS_PI 3.14159265359

// External Libs
# include <mlx.h>
# include <X11/X.h>

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
	t_size		size;
	void		*win;
	void		*display;
	t_ftm_image	*canvas;
	bool		using_mouse;
	void		(*loop_hook)(void);
	void		(*key_hook)(int key, bool down);
	void		(*exit_hook)(int code);
	void		(*mouse_hook)(t_coords coords);
}	t_ftm_window;

typedef struct s_ftm_font
{
	char		*dir;
	t_ftm_image	*characters[255];
}	t_ftm_font;

typedef struct s_ftm_pitc_config
{
	t_coords	coords;
	bool		crop;
	t_coords	crop_start;
	t_coords	crop_end;
	bool		resize;
	t_size		size;
	void		*pixel_modifier_data;
	unsigned	(*pixel_modifier)(void *data, unsigned pixel);
}	t_ftm_pitc_config;

typedef struct s_ftm_text_config
{
	char		*text;
	t_coords	coords;
	int			height;
	int			spacing;
}	t_ftm_text_config;

typedef struct s_ftm_rectangle
{
	unsigned int	background_color;
	unsigned int	border_color;
	t_size			border_size;
}	t_ftm_rectangle;

void			ftm_free_image(void *image);
t_ftm_image		*ftm_image_from_file(t_ftm_window *window, char *path, bool transparency);
t_ftm_image		*ftm_image_new(t_ftm_window *window, t_size size);
t_list			*ftm_images_from_files(t_ftm_window *window, char **file_paths, bool transparency);

void			ftm_image_clear(t_ftm_image *image);
void			ftm_put_image_to_canvas(t_ftm_image *canvas,
					t_ftm_image *image, t_ftm_pitc_config pitc);

char			*ftm_image_to_str(t_ftm_image *image);

t_ftm_font		*ftm_font_new(t_ftm_window *window, const char *dir);
void			ftm_clear_font(void *font);
void			ftm_free_font(void *font);

void			ftm_draw_text(t_ftm_image *canvas, t_ftm_font *font, t_ftm_text_config text_config);
int				ftm_get_text_size_prediction(t_ftm_font *font, t_ftm_text_config text_config);

void			ftm_clear_window(void *window);
void			ftm_free_window(void *window);
void			ftm_create_window_e(t_ftm_window *window,
					t_size size, char *title);
void			ftm_update_window(t_ftm_window *window);
void			ftm_update_hooks(t_ftm_window *window);
void			ftm_window_loop(t_ftm_window *window);
void			ftm_window_wipe(t_ftm_window *window);

unsigned int	*ftm_image_pixel(t_ftm_image *image, t_coords coords);
unsigned int	ftm_remove_pixel_transparency(unsigned int value);
void			ftm_set_pixel(unsigned int *pixel, unsigned int value);

void			ftm_draw_line(t_ftm_image *canvas, t_coords start,
					t_coords end, unsigned int color);
void			ftm_draw_line_angle(t_ftm_image *canvas, t_coords start,
					double length, unsigned int color);
void			ftm_draw_rectangle(t_ftm_image *canvas, t_coords coords,
					t_size size, t_ftm_rectangle rectangle);

#endif
