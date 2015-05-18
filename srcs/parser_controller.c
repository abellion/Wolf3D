/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_controller.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abellion <abellion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/31 16:37:02 by abellion          #+#    #+#             */
/*   Updated: 2015/04/27 21:18:09 by abellion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

char		**parser_get_points(int fd)
{
	char	*line;
	char	**tab;

	if (get_next_line(fd, &line) > 0)
	{
		tab = ft_strsplit(line, ' ');
		free(line);
		return (tab);
	}
	return (0);
}

int			parser_nb_points(char *map_path)
{
	int		i;
	int		fd;
	char	**tab;

	if ((fd = open(map_path, O_RDONLY)) == -1)
		return (0);
	i = 0;
	while ((tab = parser_get_points(fd)) > 0)
	{
		i += ft_tablen(tab);
		ft_tabdel((void ***)&tab, ft_tabdel_str);
	}
	close(fd);
	return (i);
}

t_map		*parser_put_point(int x, char *type)
{
	static int	y;
	t_map		*point;

	point = NULL;
	if ((!y && !type) || !type)
		y = -1;
	if (type)
	{
		y += (x == 0) ? 1 : 0;
		point = map_init(x, y, ft_atoi(type), 0);
	}
	return (point);
}

t_map		**parser_controller(char *map_path)
{
	int			fd;
	int			i_map;
	int			i_tab;
	char		**tab;
	t_map		**map;

	i_map = 0;
	parser_put_point(0, NULL);
	fd = open(map_path, O_RDONLY);
	map = ft_memalloc(sizeof(t_map *) * (parser_nb_points(map_path) + 1));
	if (fd == -1 || !map || map[0] != 0x0)
		return (0);
	while ((tab = parser_get_points(fd)) > 0)
	{
		i_tab = 0;
		while (tab && tab[i_tab])
		{
			map[i_map] = parser_put_point(i_tab, tab[i_tab]);
			i_tab++, i_map++;
		}
		ft_tabdel((void ***)&tab, ft_tabdel_str);
	}
	close(fd);
	map[i_map] = NULL;
	return (map);
}
