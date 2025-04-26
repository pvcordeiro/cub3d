/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 21:53:37 by afpachec          #+#    #+#             */
/*   Updated: 2025/04/26 22:03:59 by afpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

t_cub3d *cub3d(void)
{
    static t_cub3d  singleton;

    return (&singleton);
}

void    cub3d_exit(void)
{
    exit(cub3d()->error);
}