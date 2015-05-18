/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abellion <abellion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/16 17:48:48 by abellion          #+#    #+#             */
/*   Updated: 2015/04/29 12:08:48 by abellion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H

# include "../mlx_lib/mlx.h"
# include "../mlx_lib/X.h"
# include "../gnl/get_next_line.h"
# include "../libft/includes/libft.h"
# include <math.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>

# define SOFT_NAME			"Wolf3D"
# define WIDTH_SCREEN		1200
# define HEIGHT_SCREEN		750
# define WALK_SPEED			(BLOCK_SIZE / 10)
# define TURN_SPEED			6
# define C_SKY				0x2ACBE6
# define C_FLOOR			0x034001
# define C_NORTH			0x553726
# define C_SOUTH			0x745132
# define C_EAST				0x876F60
# define C_WEST				0xD7B8AF
# define C_WIN				0xFFFFFF

# define BLOCK_SIZE			24000
# define PROJ_MID			(HEIGHT_SCREEN / 2)
# define PROJ_DIST			(WIDTH_SCREEN / 2) / 0.5773502692

# define ANGLE_INC			(60.0 / WIDTH_SCREEN)
# define TO_RAD(x)			(x * M_PI) / 180
# define TO_DEG(x)			(x * 180) / M_PI

# define D_VERTICAL			0
# define D_HORIZONTAL		1
# define D_TOP				1
# define D_BOTTOM			2
# define D_RIGHT			3
# define D_LEFT				4
# define K_FORWARD(x)		(x == 126 || x == 13)
# define K_BACKWARD(x)		(x == 125 || x == 1)
# define K_RIGHT(x)			(x == 124 || x == 2)
# define K_LEFT(x)			(x == 123 || x == 0)
# define K_ADD_B(x)			(x == 49)
# define K_REM_B(x)			(x == 7)
# define K_MAP(x)			(x == 18 || x == 19 || x == 20 || x == 21)
# define K_QUIT(x)			(x == 53)

/*
** STRUCTURES
*/
typedef struct	s_env
{
	void			*mlx;
	void			*win;
	void			*img;
}				t_env;

typedef struct	s_map
{
	double			x;
	double			y;
	int				type;
	double			dist;
}				t_map;

typedef struct	s_player
{
	double			x;
	double			y;
	double			angle;
}				t_player;

typedef struct	s_angle
{
	double			val;
	double			cos;
	double			sin;
	double			tan;
}				t_angle;

typedef struct	s_all
{
	struct s_env	*env;
	struct s_map	**map;
	struct s_player	*player;
	struct s_angle	**angles;
	char			**maps;
}				t_all;

/*
** PARSER
*/
t_map			**parser_controller(char *path);
t_map			*parser_put_point(int x, char *type);
int				parser_nb_points(char *map_path);
char			**parser_get_points(int fd);

/*
** ENV
*/
t_env			*env_init(void);
t_env			*env_make(t_env *env);
void			env_del(t_env **env);

/*
** PLAYER
*/
t_player		*player_init(void);
t_player		*player_get_pos(t_map **map);
void			player_del(t_player **player);

/*
** MAP
*/
t_map			*map_init(double x, double y, int type, double dist);
void			map_del_point(t_map **point);
void			map_del_tab(t_map ***map);
int				*map_get_limits(t_map **map);
t_map			*map_get(t_map **map, double x, double y);

/*
** ANGLE
*/
t_angle			**angle_controller(void);
t_angle			*angle_init(double val);
void			angle_del(t_angle ***angle);
double			angle_check(double angle);
t_angle			*angle_get(t_angle **angles, double angle);

/*
** RAY
*/
t_map			*ray_controller(t_map **map, t_player *player, t_angle *angle);
int				*ray_dir(double angle);

/*
** DRAW
*/
void			put_pixel_on_img(void *img, int x, int y, int color);
void			put_ray(t_env *env, t_map *beg, t_map *end, int color);
int				draw_controller(t_all *all);
int				draw_get_color(t_map **map, t_map *ray);
void			draw_ray(t_env *env, t_map *ray, int x, int color);

/*
** KEY
*/
void			key_controller(int key, t_all *all);
void			key_quit(t_all **all);
void			key_move_walk(int key, t_all *all);
void			key_move_turn(int key, t_all *all);
void			key_change_block(int key, t_all *all);
void			key_change_map(int key, t_all *all);
t_map			*key_dist(t_all *all, int dist);

/*
** MAIN
*/
int				expose(t_env *env);
int				key_press(int key, t_all *all);
t_all			*all_construct(char **maps, int map_nb, t_angle **angles);
void			all_destruct(t_all **all);

#endif
