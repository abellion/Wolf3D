/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_move.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abellion <abellion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/27 17:29:04 by abellion          #+#    #+#             */
/*   Updated: 2015/04/28 15:42:54 by abellion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	key_move_walk(int key, t_all *all)
{
	int			mult;
	t_map		*dist;
	t_map		new_pos;
	t_map		*dist_secure;

	dist = key_dist(all, WALK_SPEED);
	mult = (K_FORWARD(key)) ? 1 : -1;
	dist_secure = key_dist(all, (BLOCK_SIZE / 3));
	new_pos.x = all->player->x + ((dist->x + dist_secure->x) * mult);
	new_pos.y = all->player->y + ((dist->y + dist_secure->y) * mult);
	if (map_get(all->map, new_pos.x, new_pos.y)->type <= 0)
	{
		all->player->x = new_pos.x - (dist_secure->x * mult);
		all->player->y = new_pos.y - (dist_secure->y * mult);
		draw_controller(all);
	}
	map_del_point(&dist);
	map_del_point(&dist_secure);
}

void	key_move_turn(int key, t_all *all)
{
	if (K_LEFT(key))
		all->player->angle = angle_check(all->player->angle + TURN_SPEED);
	else
		all->player->angle = angle_check(all->player->angle - TURN_SPEED);
	draw_controller(all);
}

void	key_change_block(int key, t_all *all)
{
	t_map		tmp;
	t_map		*pos;
	t_map		*dist;

	dist = key_dist(all, BLOCK_SIZE + (BLOCK_SIZE / 3));
	tmp.x = all->player->x + dist->x;
	tmp.y = all->player->y + dist->y;
	pos = map_get(all->map, tmp.x, tmp.y);
	if (pos->type <= 0 && K_ADD_B(key))
	{
		pos->type = 1;
		draw_controller(all);
	}
	else if (pos->type > 0 && K_REM_B(key) && pos->x > 0 && pos->y > 0)
	{
		pos->type = 0;
		draw_controller(all);
	}
	map_del_point(&dist);
}

void	key_change_map(int key, t_all *all)
{
	t_all		*tmp;
	t_map		**map_tmp;
	t_player	*player_tmp;

	if (ft_tablen(all->maps) < (key - 18 + 1))
		return ;
	map_tmp = parser_controller(all->maps[key - 18]);
	player_tmp = player_get_pos(map_tmp);
	if (map_tmp && player_tmp)
	{
		tmp = all;
		map_del_tab(&(tmp->map));
		player_del(&(tmp->player));
		all->map = map_tmp;
		all->player = player_tmp;
		draw_controller(all);
	}
}
