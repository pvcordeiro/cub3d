/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 00:41:46 by afpachec          #+#    #+#             */
/*   Updated: 2025/05/28 00:42:00 by afpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "billboards.h"

bool	cmp_billboards(void *data, t_billboard *a, t_billboard *b)
{
	return (ft_distance(*((t_coords *)data), a->entity.coords)
		< ft_distance(*((t_coords *)data), b->entity.coords));
}
