/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_controller.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abellion <abellion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/01 14:34:35 by abellion          #+#    #+#             */
/*   Updated: 2015/04/25 22:10:59 by abellion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

t_env		*env_init(void)
{
	t_env	*env;

	if (!(env = (t_env *)malloc(sizeof(t_env))))
		return (0);
	env->mlx = NULL;
	env->win = NULL;
	env->img = NULL;
	return (env);
}

void		env_del(t_env **env)
{
	if (env && *env)
	{
		mlx_destroy_image((*env)->mlx, (*env)->img);
		mlx_destroy_window((*env)->mlx, (*env)->win);
		free((*env)->mlx);
		free(*env);
		*env = NULL;
	}
}

t_env		*env_make(t_env *env)
{
	if (!env)
		return (0);
	env->mlx = mlx_init();
	env->win = mlx_new_window(env->mlx, WIDTH_SCREEN, HEIGHT_SCREEN, SOFT_NAME);
	env->img = mlx_new_image(env->mlx, WIDTH_SCREEN + 1, HEIGHT_SCREEN + 1);
	return (env);
}
