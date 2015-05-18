/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcouet <tcouet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/13 16:01:46 by tcouet            #+#    #+#             */
/*   Updated: 2015/04/27 22:01:59 by abellion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		read_fd(int fd, char **part)
{
	int		ret;
	int		stop;
	char	*old_part;
	char	buffer[BUFF_SIZE + 1];

	ret = 0;
	stop = 0;
	buffer[0] = '\0';
	while (!stop && (ret = read(fd, buffer, BUFF_SIZE)) > 0)
	{
		old_part = *part;
		buffer[ret] = '\0';
		*part = (!*part) ? ft_strdup("") : *part;
		*part = ft_strjoin(*part, buffer);
		ft_strdel(&old_part);
		stop = (ft_strchr(buffer, '\n')) ? 1 : 0;
	}
	if (ret <= 0 && !ft_strlen(buffer))
		return (ret);
	return (1);
}

char	*get_line(char **part)
{
	int		i;
	char	*old_part;
	char	*line;

	i = 0;
	while ((*part)[i] != '\n' && (*part)[i] != '\0')
		i++;
	old_part = *part;
	line = ft_strsub(*part, 0, i);
	if ((*part)[i])
		*part = ft_strsub(*part, i + 1, ft_strlen(*part) - i);
	else
		*part = NULL;
	ft_strdel(&old_part);
	return (line);
}

int		get_next_line(int const fd, char **line)
{
	static char		*part;
	int				ret;

	if (fd < 0 || !line)
		return (-1);
	ret = (!part || !ft_strchr(part, '\n')) ? read_fd(fd, &part) : 1;
	if (ret == 1)
	{
		*line = get_line(&part);
		return (1);
	}
	return (ret);
}
