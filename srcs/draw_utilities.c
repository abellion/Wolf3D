/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utilities.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abellion <abellion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/27 16:30:06 by abellion          #+#    #+#             */
/*   Updated: 2015/04/27 16:30:12 by abellion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	put_pixel_on_img(void *img, int x, int y, int color)
{
	char	*data;
	int		bpp;
	int		sizeline;
	int		edian;
	int		pos;

	if (x >= 0 && x <= WIDTH_SCREEN && y >= 0 && y <= HEIGHT_SCREEN)
	{
		data = mlx_get_data_addr(img, &bpp, &sizeline, &edian);
		pos = (x * (bpp / 8)) + (y * sizeline);
		data[pos] = (color & 0xFF);
		data[pos + 1] = (color & 0xFF00) >> 8;
		data[pos + 2] = (color & 0xFF0000) >> 16;
	}
}

void	put_ray(t_env *env, t_map *beg, t_map *end, int color)
{
	int		i;

	i = 0;
	while (i < end->y)
	{
		put_pixel_on_img(env->img, beg->x, beg->y + i, color);
		i++;
	}
}
