/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 17:14:52 by afpachec          #+#    #+#             */
/*   Updated: 2025/04/27 00:44:31 by afpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <mlx.h>

# include <ft_error.h>
# include <ft_utils.h>

# include <stdio.h>
# include <stdbool.h>
# include <stdlib.h>

typedef struct s_window
{
	int		height;
	int		width;
	void	*win;
	void	*mlx;
	bool	initialized;
}	t_window;

typedef struct s_cub3d
{
	t_window	window;
	t_error		error;
}	t_cub3d;

t_cub3d	*cub3d(void);
void	cub3d_exit(int code);
bool	create_window(t_window *window, int width, int height, char *title);
void	destroy_window(t_window *window);

#endif
