/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_controller.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abellion <abellion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/01 15:52:52 by abellion          #+#    #+#             */
/*   Updated: 2015/04/27 21:27:00 by abellion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

t_player	*player_init(void)
{
	t_player	*player;

	if (!(player = (t_player *)malloc(sizeof(t_player))))
		return (0);
	player->x = 0;
	player->y = 0;
	player->angle = 0;
	return (player);
}

void		player_del(t_player **player)
{
	if (player && *player)
	{
		free(*player);
		*player = NULL;
	}
}

t_player	*player_get_pos(t_map **map)
{
	int			i;
	t_player	*player;

	i = 0;
	while (map && map[i])
	{
		if (map[i]->type == -1)
		{
			player = player_init();
			player->x = map[i]->x * BLOCK_SIZE + (BLOCK_SIZE / 2);
			player->y = map[i]->y * BLOCK_SIZE + (BLOCK_SIZE / 2);
			player->angle = 90;
			return (player);
		}
		i++;
	}
	return (0);
}
