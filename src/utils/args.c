/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 08:42:58 by afpachec          #+#    #+#             */
/*   Updated: 2025/04/27 08:52:52 by afpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

char	*get_map_from_args(int argc, char **argv)
{
	if (argc != 2 || !argv || !argv[0] || !argv[1] || argv[2])
		return (ft_error(ERROR_INVALID_ARGS), NULL);
	ft_error(ERROR_NO_ERROR);
	return (argv[1]);
}
