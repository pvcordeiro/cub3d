/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paude-so <paude-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 21:53:37 by afpachec          #+#    #+#             */
/*   Updated: 2025/06/06 20:54:53 by paude-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	*hashmap_get_with_identifier(t_hashmap *hashmap, char identifier, char *rest)
{
	char	*key;
	void	*data;

	key = ft_strdup(rest);
	if (identifier)
		key = (free(key), ft_strf("%c_%s", identifier, rest));
	data = ft_hashmap_get_value(hashmap, key);
	return (free(key), data);
}

t_cub3d	*cub3d(void)
{
	static t_cub3d	singleton;

	return (&singleton);
}

void	cub3d_exit(int code)
{
	free_map(cub3d()->curr_map);
	clear_game(&cub3d()->game);
	clear_sprite(&cub3d()->placeholder);
	ft_restore_screen_mode((t_xvar *)cub3d()->window.display, (t_win_list *)cub3d()->window.win);
	ftm_clear_window(&cub3d()->window);
	fta_destroy();
	exit(code);
}
