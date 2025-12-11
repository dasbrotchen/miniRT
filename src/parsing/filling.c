/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filling.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgrangeo <rgrangeo@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 02:28:00 by rgrangeo          #+#    #+#             */
/*   Updated: 2024/11/14 12:16:33 by pantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "get_next_line.h"
#include "parsing.h"
#include <errno.h>

static int	distributor(char **line, t_scene *scene)
{
	if (ft_strncmp(line[0], "A", 1) == 0)
		return (create_ambient_lightning(line, &scene->ambient));
	if (ft_strncmp(line[0], "C", 1) == 0)
		return (create_camera(line, &scene->camera));
	if (ft_strncmp(line[0], "L", 1) == 0)
		return (create_light(line, scene->light_sources.source));
	if (ft_strncmp(line[0], "sp", 2) == 0)
		return (create_sphere(line, scene));
	if (ft_strncmp(line[0], "pl", 2) == 0)
		return (create_plane(line, scene));
	if (ft_strncmp(line[0], "cy", 2) == 0)
		return (create_cylinder(line, scene));
	if (ft_strncmp(line[0], "co", 2) == 0)
		return (create_cone(line, scene));
	return (NONE);
}

void	origin_scene(t_memory_scene m_scene, t_scene *scene)
{
	scene->objs = m_scene.object_m;
	scene->light_sources.source = m_scene.light_m;
}

static int	next_element(int retval, char **split, char *line,
		t_scene *scene)
{
	free_split(split);
	free(line);
	if (retval == ERROR)
		return (1);
	else if (retval == OBJECT)
		scene->objs++;
	else if (retval == LIGHT)
		scene->light_sources.source++;
	return (0);
}

static int	gnl_malloc_error(t_memory_scene m_scene, t_scene *scene,
		char *line)
{
	if (errno == ENOMEM && !line)
	{
		origin_scene(m_scene, scene);
		return (-1);
	}
	return (0);
}

int	parse_element(int fd, t_scene *scene)
{
	char			*line;
	char			**split;
	t_memory_scene	m_scene;

	m_scene.object_m = scene->objs;
	m_scene.light_m = scene->light_sources.source;
	line = get_next_line(fd);
	if (gnl_malloc_error(m_scene, scene, line))
		return (putstr_error("Malloc error"));
	while (line)
	{
		split = ft_split(line, ' ');
		if (split == NULL)
			return (split_scene_malloc_error(line, fd, m_scene, scene));
		if (next_element(distributor(split, scene), split, line, scene))
		{
			origin_scene(m_scene, scene);
			return (free_gnl(fd));
		}
		line = get_next_line(fd);
		if (gnl_malloc_error(m_scene, scene, line))
			return (putstr_error("Malloc error"));
	}
	origin_scene(m_scene, scene);
	return (1);
}
