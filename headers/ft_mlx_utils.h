/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mlx_utils.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 16:46:27 by afpachec          #+#    #+#             */
/*   Updated: 2025/05/06 16:59:18 by afpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MLX_UTILS_H
# define FT_MLX_UTILS_H

// External Libs
# include <mlx.h>

// Internal Libs
# include <ft_utils.h>
# include <ft_error.h>

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

void	free_image(void *image);
t_image	*image_from_file(t_window *window, char *path);
t_image	*image_new(t_window *window, t_size size);
t_list	*images_from_files(t_window *window, char **file_paths);

void	free_window(void *window);
void	create_window_e(t_window *window, t_size size, char *title);
void	update_window(t_window *window);


#endif