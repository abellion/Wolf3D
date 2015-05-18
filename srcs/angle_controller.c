/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   angle_controller.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abellion <abellion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/21 16:18:02 by abellion          #+#    #+#             */
/*   Updated: 2015/04/27 19:05:42 by abellion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

t_angle		*angle_init(double val)
{
	t_angle		*angle;

	if (!(angle = (t_angle *)malloc(sizeof(t_angle))))
		return (0);
	angle->val = val;
	angle->cos = cos(TO_RAD(val));
	angle->sin = sin(TO_RAD(val));
	angle->tan = tan(TO_RAD(val));
	return (angle);
}

void		angle_del(t_angle ***angles)
{
	int		i;

	i = 0;
	if (angles && *angles)
	{
		while ((*angles)[i])
		{
			free((*angles)[i]);
			i++;
		}
		free(*angles);
		*angles = NULL;
	}
}

double		angle_check(double angle)
{
	if (angle > 360)
		return (angle - 360);
	else if (angle < 0)
		return (angle + 360);
	return (angle);
}

t_angle		*angle_get(t_angle **angles, double angle)
{
	double		nb;

	nb = (angle / ANGLE_INC);
	return (angles[(int)round(nb)]);
}

t_angle		**angle_controller(void)
{
	int			i;
	double		angle;
	t_angle		**angles;
	int			nb_angles;

	i = 0;
	angle = 0;
	nb_angles = (1 / ANGLE_INC) * 360;
	if (!(angles = (t_angle **)malloc(sizeof(t_angle *) * (nb_angles + 2))))
		return (0);
	while (i <= nb_angles)
	{
		angles[i] = angle_init(angle);
		angle += ANGLE_INC;
		i++;
	}
	angles[i] = NULL;
	return (angles);
}
