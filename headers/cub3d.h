/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 17:14:52 by afpachec          #+#    #+#             */
/*   Updated: 2025/04/26 22:47:12 by afpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

#include <stdio.h>
#include <mlx.h>
#include <stdbool.h>
#include <error.h>
#include <stdlib.h>

typedef struct  s_window
{
    int     height;
    int     width;
    void    *win;
    void    *mlx;
}   t_window;

typedef struct  s_cub3d
{
    t_window    window;
    t_error     error;
}   t_cub3d;

t_cub3d *cub3d(void);
void    error(t_error _error);
bool    create_window(t_window *window, int width, int height, char *title);

#endif
