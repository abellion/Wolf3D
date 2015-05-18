/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_controller.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abellion <abellion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/03 15:33:41 by abellion          #+#    #+#             */
/*   Updated: 2015/04/27 21:39:13 by abellion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		draw_ray(t_env *env, t_map *ray, int x, int color)
{
	t_map			beg;
	t_map			end;
	int				wall_height;

	wall_height = ceil((BLOCK_SIZE / floor(ray->dist)) * PROJ_DIST);
	beg.x = x;
	end.x = x;
	beg.y = 0;
	end.y = PROJ_MID - (wall_height / 2);
	put_ray(env, &beg, &end, C_SKY);
	beg.y = PROJ_MID - (wall_height / 2);
	end.y = beg.y + wall_height;
	put_ray(env, &beg, &end, color);
	beg.y = (PROJ_MID - (wall_height / 2)) + wall_height;
	end.y = HEIGHT_SCREEN;
	put_ray(env, &beg, &end, C_FLOOR);
}

int			draw_get_color(t_map **map, t_map *ray)
{
	t_map	*right;
	t_map	*left;

	if (ray->type == 2)
		return (C_WIN);
	right = map_get(map, ray->x + 1, ray->y);
	left = map_get(map, ray->x - 1, ray->y);
	if (right->type > 0 && left->type > 0)
		return (((int)ray->y % BLOCK_SIZE) ? C_NORTH : C_SOUTH);
	else
		return (((int)ray->x % BLOCK_SIZE) ? C_EAST : C_WEST);
}

int			draw_controller(t_all *all)
{
	int				x;
	t_map			*ray;
	t_angle			*angle;

	x = 0;
	if (!all || !all->env || !all->map || !all->player || !all->angles)
		return (0);
	angle = angle_get(all->angles, angle_check(all->player->angle + 30));
	while (x <= WIDTH_SCREEN)
	{
		ray = ray_controller(all->map, all->player, angle);
		draw_ray(all->env, ray, x, draw_get_color(all->map, ray));
		angle = angle_get(all->angles, angle_check(angle->val - ANGLE_INC));
		map_del_point(&ray);
		x++;
	}
	expose(all->env);
	return (0);
}
