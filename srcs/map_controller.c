/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_controller.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abellion <abellion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/02 17:32:19 by abellion          #+#    #+#             */
/*   Updated: 2015/04/27 21:18:16 by abellion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

t_map		*map_init(double x, double y, int type, double dist)
{
	t_map			*map;

	if (!(map = (t_map *)malloc(sizeof(t_map))))
		return (0);
	map->x = x;
	map->y = y;
	map->type = type;
	map->dist = dist;
	return (map);
}

void		map_del_point(t_map **point)
{
	if (point)
	{
		free(*point);
		*point = NULL;
	}
}

void		map_del_tab(t_map ***map)
{
	int		i;

	if (map && *map)
	{
		i = 0;
		while ((*map)[i])
		{
			map_del_point(&(*map)[i]);
			i++;
		}
		free(*map);
		*map = NULL;
	}
}

int			*map_get_limits(t_map **map)
{
	int				x;
	int				y;
	int				i;
	static int		limits[2];

	i = 0;
	x = 0;
	y = 0;
	while (map && map[i])
	{
		if (y == 0 && i > 0 && map[i]->y == map[i - 1]->y)
			x++;
		else if (i > 0 && map[i]->y != map[i - 1]->y)
			y++;
		i++;
	}
	limits[0] = x;
	limits[1] = y;
	return (limits);
}

t_map		*map_get(t_map **map, double x, double y)
{
	static int		*limits;
	static t_map	**old_map;

	if (&old_map != &map)
		limits = map_get_limits(map);
	if (x > (limits[0] * BLOCK_SIZE) || x < 0)
		return (map[0]);
	if (y > (limits[1] * BLOCK_SIZE) || y < 0)
		return (map[0]);
	x = (int)(x / BLOCK_SIZE);
	y = (int)(y / BLOCK_SIZE);
	return (map[(int)(y * limits[0] + x + y)]);
}
