/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_utilities.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abellion <abellion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/03 14:50:12 by abellion          #+#    #+#             */
/*   Updated: 2015/04/24 18:29:22 by abellion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int		*ray_dir(double angle)
{
	static int		dir[2];

	dir[D_VERTICAL] = -1;
	dir[D_HORIZONTAL] = -1;
	if (angle >= 0 && angle <= 180)
		dir[D_VERTICAL] = D_TOP;
	else if (angle >= 180 && angle <= 360)
		dir[D_VERTICAL] = D_BOTTOM;
	if ((angle >= 0 && angle <= 90) || (angle >= 270 && angle <= 360))
		dir[D_HORIZONTAL] = D_RIGHT;
	else if ((angle >= 90 && angle <= 180) || (angle <= 270 && angle >= 180))
		dir[D_HORIZONTAL] = D_LEFT;
	return (dir);
}
