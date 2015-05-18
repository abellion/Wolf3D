/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abellion <abellion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/16 17:48:19 by abellion          #+#    #+#             */
/*   Updated: 2015/04/27 21:18:06 by abellion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int		expose(t_env *env)
{
	mlx_put_image_to_window(env->mlx, env->win, env->img, 0, 0);
	return (0);
}

int		key_press(int key, t_all *all)
{
	key_controller(key, all);
	return (0);
}

t_all	*all_construct(char **maps, int map_nb, t_angle **angles)
{
	t_all		*all;

	if (!(all = (t_all *)malloc(sizeof(t_all))))
		return (0);
	all->angles = angles;
	all->map = parser_controller(maps[map_nb]);
	all->player = player_get_pos(all->map);
	all->maps = maps;
	return (all);
}

void	all_destruct(t_all **all)
{
	t_all	*tmp;

	if (all)
	{
		tmp = *all;
		map_del_tab(&(tmp->map));
		player_del(&(tmp->player));
		free(*all);
		*all = NULL;
	}
}

int		main(int ac, char **av)
{
	t_all		*all;
	t_angle		**angles;

	angles = angle_controller();
	all = all_construct(&av[1], 0, angles);
	if (ac >= 2 && ac <= 5 && all && all->map && all->player && all->angles)
	{
		all->env = env_make(env_init());
		draw_controller(all);
		mlx_expose_hook(all->env->win, expose, all->env);
		mlx_hook(all->env->win, KeyPress, KeyRelease, key_press, all);
		mlx_loop(all->env->mlx);
	}
	return (0);
}
