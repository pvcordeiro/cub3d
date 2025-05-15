/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game4.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 22:43:09 by afpachec          #+#    #+#             */
/*   Updated: 2025/05/15 22:50:39 by afpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void	kill_threads(t_game *game)
{
	int	i;

	i = -1;
	while (++i < RENDERING_THREADS)
		ftt_free_thread(game->rendering_threads[i]);
}

void	init_threads_e(t_game *game)
{
	int	i;

	fte_set(ERROR_NO_ERROR);
	i = -1;
	while (++i < RENDERING_THREADS)
	{
		game->rendering_threads[i] = ftt_thread_new();
		if (!game->rendering_threads[i])
			return (fte_set(ERROR_THREAD_INIT));
	}
}
