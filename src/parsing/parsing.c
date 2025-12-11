/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgrangeo <rgrangeo@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 18:21:35 by rgrangeo          #+#    #+#             */
/*   Updated: 2024/11/14 18:42:58 by pantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include <fcntl.h>
#include "get_next_line.h"

void	free_scene(t_scene *scene)
{
	int			i;
	t_bumpmap	*bm;

	i = 0;
	if (scene->objs == NULL)
		return ;
	while (scene->objs[i] != NULL)
	{
		if (scene->objs[i]->object != NULL)
		{
			if (scene->objs[i]->texture)
			{
				bm = (t_bumpmap *)scene->objs[i]->texture;
				if (scene->objs[i]->has_img)
					mlx_destroy_image(scene->inst, bm->img_ptr);
				free(bm);
			}
			free(scene->objs[i]->object);
		}
		free(scene->objs[i]);
		i++;
	}
	if (scene->light_sources.source != NULL)
		free(scene->light_sources.source);
	free(scene->objs);
}

static int	init_object(t_nbr_element nbr_element, t_scene *scene)
{
	unsigned int	i;

	i = 0;
	scene->objs = malloc(sizeof(t_object *) * (nbr_element.object + 1));
	if (scene->objs == NULL)
		return (putstr_error("Malloc error"));
	scene->objs[nbr_element.object] = NULL;
	while (i < nbr_element.object)
	{
		scene->objs[i] = malloc(sizeof(t_object));
		if (scene->objs[i] == NULL)
		{
			free_scene(scene);
			putstr_error("Malloc error");
			return (ERROR);
		}
		scene->objs[i]->object = NULL;
		i++;
	}
	return (1);
}

static int	close_return(int fd, int error, char *msg, t_scene *scene)
{
	close(fd);
	if (msg)
		putstr_error(msg);
	if (scene)
		free_scene(scene);
	return (error);
}

int	parsing(const char *path, t_scene *scene)
{
	t_nbr_element	nbr_element;
	int				fd;

	scene->light_sources.source = NULL;
	fd = open_file(path);
	if (fd == -1)
		return (ERROR);
	nbr_element = element_counter(fd);
	if (nbr_element.error == ERROR)
		return (ERROR);
	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (putstr_error("Error opening the scene"));
	scene->light_sources.nb_lights = nbr_element.light;
	if (init_object(nbr_element, scene) == ERROR)
		return (close_return(fd, ERROR, NULL, NULL));
	scene->light_sources.source = malloc(sizeof(t_light) * (nbr_element.light));
	if (scene->light_sources.source == NULL)
		return (close_return(fd, ERROR, "Malloc error", scene));
	if (parse_element(fd, scene) == ERROR)
		return (close_return(fd, ERROR, NULL, scene));
	return (close_return(fd, 1, NULL, NULL));
}
