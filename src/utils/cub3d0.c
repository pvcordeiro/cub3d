/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 21:53:37 by afpachec          #+#    #+#             */
/*   Updated: 2025/06/25 21:13:37 by afpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

t_cub3d	*cub3d(void)
{
	static t_cub3d	singleton;

	return (&singleton);
}

void	cub3d_exit(int code)
{
	pthread_mutex_lock(&cub3d()->game_mutex);
	free_game(cub3d()->game);
	cub3d()->game = NULL;
	free_map(cub3d()->curr_map);
	free_map(cub3d()->prev_map);
	cub3d()->curr_map = NULL;
	cub3d()->prev_map = NULL;
	clear_sprite(&cub3d()->placeholder);
	ftm_clear_window(&cub3d()->window);
	fta_destroy();
	pthread_mutex_unlock(&cub3d()->game_mutex);
	pthread_mutex_destroy(&cub3d()->game_mutex);
	exit(code);
}
