/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_controller.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abellion <abellion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/02 17:28:39 by abellion          #+#    #+#             */
/*   Updated: 2015/04/27 17:42:43 by abellion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

t_map	*ray_get_x(t_map **map, t_player *player, t_angle *angle, int *dir)
{
	t_map		inc;
	t_map		tmp;
	t_map		*pos;

	inc.x = fabs(BLOCK_SIZE / angle->tan);
	inc.x = (dir[D_HORIZONTAL] == D_RIGHT) ? inc.x : -inc.x;
	inc.y = (dir[D_VERTICAL] == D_TOP) ? -BLOCK_SIZE : BLOCK_SIZE;
	tmp.y = (int)(player->y / BLOCK_SIZE) * BLOCK_SIZE;
	tmp.y += (dir[D_VERTICAL] == D_TOP) ? -1 : BLOCK_SIZE;
	tmp.x = player->x + (player->y - tmp.y) / angle->tan;
	pos = map_get(map, tmp.x, tmp.y);
	while (pos->type <= 0)
	{
		tmp.x += inc.x;
		tmp.y += inc.y;
		pos = map_get(map, tmp.x, tmp.y);
	}
	return (map_init(tmp.x, tmp.y, pos->type, 0));
}

t_map	*ray_get_y(t_map **map, t_player *player, t_angle *angle, int *dir)
{
	t_map		inc;
	t_map		tmp;
	t_map		*pos;

	inc.x = (dir[D_HORIZONTAL] == D_RIGHT) ? BLOCK_SIZE : -BLOCK_SIZE;
	inc.y = fabs(BLOCK_SIZE * angle->tan);
	inc.y = (dir[D_VERTICAL] == D_TOP) ? -inc.y : inc.y;
	tmp.x = (int)(player->x / BLOCK_SIZE) * BLOCK_SIZE;
	tmp.x += (dir[D_HORIZONTAL] == D_RIGHT) ? BLOCK_SIZE : -1;
	tmp.y = player->y + (player->x - tmp.x) * angle->tan;
	pos = map_get(map, tmp.x, tmp.y);
	while (pos->type <= 0)
	{
		tmp.x += inc.x;
		tmp.y += inc.y;
		pos = map_get(map, tmp.x, tmp.y);
	}
	return (map_init(tmp.x, tmp.y, pos->type, 0));
}

double	ray_get_dist(t_player *player, t_angle *angle, t_map *ray)
{
	double		x_tmp;
	double		y_tmp;
	double		dist;

	x_tmp = ray->x - player->x;
	y_tmp = ray->y - player->y;
	dist = sqrt(pow(x_tmp, 2) + pow(y_tmp, 2));
	dist *= cos(TO_RAD(fabs(angle->val - player->angle)));
	return (dist);
}

t_map	*ray_controller(t_map **map, t_player *player, t_angle *angle)
{
	t_map		*ray_x;
	t_map		*ray_y;
	int			*dir;

	if (!map || !player || !angle)
		return (0);
	dir = ray_dir(angle->val);
	ray_x = ray_get_x(map, player, angle, dir);
	ray_y = ray_get_y(map, player, angle, dir);
	ray_x->dist = ray_get_dist(player, angle, ray_x);
	ray_y->dist = ray_get_dist(player, angle, ray_y);
	if (ray_x->dist < ray_y->dist)
		return (map_del_point(&ray_y), ray_x);
	return (map_del_point(&ray_x), ray_y);
}
