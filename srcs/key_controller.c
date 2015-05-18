/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_controller.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abellion <abellion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/04 19:35:51 by abellion          #+#    #+#             */
/*   Updated: 2015/04/27 18:40:31 by abellion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		key_quit(t_all **all)
{
	t_all				*tmp;

	tmp = *all;
	env_del(&(tmp->env));
	angle_del(&(tmp->angles));
	all_destruct(all);
	exit(EXIT_SUCCESS);
}

t_map		*key_dist(t_all *all, int dist)
{
	int			*dir;
	t_map		*tmp;
	t_angle		*angle;

	tmp = map_init(0, 0, 0, 0);
	dir = ray_dir(all->player->angle);
	angle = angle_get(all->angles, all->player->angle);
	tmp->x = fabs(dist * angle->cos);
	tmp->y = fabs(dist * angle->sin);
	tmp->x = (dir[D_HORIZONTAL] == D_RIGHT) ? tmp->x : -tmp->x;
	tmp->y = (dir[D_VERTICAL] == D_TOP) ? -tmp->y : tmp->y;
	return (tmp);
}

void		key_controller(int key, t_all *all)
{
	if (K_QUIT(key))
		key_quit(&all);
	else if (K_RIGHT(key) || K_LEFT(key))
		key_move_turn(key, all);
	else if (K_FORWARD(key) || K_BACKWARD(key))
		key_move_walk(key, all);
	else if (K_ADD_B(key) || K_REM_B(key))
		key_change_block(key, all);
	else if (K_MAP(key))
		key_change_map(key, all);
}
