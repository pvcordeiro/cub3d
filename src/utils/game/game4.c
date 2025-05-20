/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game4.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 22:43:09 by afpachec          #+#    #+#             */
/*   Updated: 2025/05/20 17:54:24 by afpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void	kill_threads(t_game *game)
{
	int	i;

	i = -1;
	while (++i < CAMERA_THREADS)
		ftt_free_thread(game->camera_threads[i]);
}

void	init_threads_e(t_game *game)
{
	int	i;

	fte_set(ERROR_NO_ERROR);
	i = -1;
	while (++i < CAMERA_THREADS)
	{
		game->camera_threads[i] = ftt_thread_new();
		if (!game->camera_threads[i])
			return (fte_set(ERROR_THREAD_INIT));
	}
}
