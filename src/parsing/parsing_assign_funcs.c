/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_assign_funcs.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pantoine <pantoine@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 15:15:45 by pantoine          #+#    #+#             */
/*   Updated: 2024/11/14 12:17:32 by pantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "compute.h"
#include "libft.h"

void	*object_filler_error(void *obj, void *texture, char *msg)
{
	free(texture);
	free(obj);
	if (msg != NULL)
		putstr_error(msg);
	return (NULL);
}

int	type_object(char *type)
{
	if (!ft_strncmp(type, "checkerboard", 12))
		return (CHECKERED);
	if (!ft_strncmp(type, "xpm=", 4))
		return (TEXTURED);
	return (NORMAL);
}

int	parse_textured_lighting_intensities(char **line,
				int *error, t_scene *scene, int type)
{
	if (type == CHECKERED)
	{
		if (parse_lighting_intensities(scene->objs[0],
				line + 4, error) == ERROR)
			return (ERROR);
	}
	else if (type == TEXTURED)
	{
		if (parse_lighting_intensities(scene->objs[0],
				line + 1, error) == ERROR)
			return (ERROR);
	}
	return (0);
}

int	assign_function_ptrs(int type, t_scene *scene,
				char **line, int shape)
{
	int	min_args;

	min_args = 4 * (shape == SPHERE || shape == PLANE)
		+ 6 * (shape == CYLINDER || shape == CONE);
	scene->objs[0]->get_normal_vec = scene->funcptrs.normal_get_ptr \
		[shape][NORMAL_OFFSET];
	if (type == CHECKERED)
		scene->objs[0]->get_colour = scene->funcptrs.colour_get_ptr \
			[shape][CHECKERED_OFFSET];
	else if (type == TEXTURED)
	{
		scene->objs[0]->get_colour = scene->funcptrs.colour_get_ptr \
			[shape][IMG_TEXTURE_OFFSET];
		if (!ft_strncmp(line[min_args], "bump=on", 7))
			scene->objs[0]->get_normal_vec = scene->funcptrs.normal_get_ptr \
				[shape][BUMP_OFFSET];
		else if (ft_strncmp(line[min_args], "bump=off", 8))
			return (putstr_error("Specify bumps with bump=on or bump=off"));
	}
	else if (type == NORMAL)
		scene->objs[0]->get_colour = scene->funcptrs.colour_get_ptr \
			[shape][NORMAL_OFFSET];
	scene->objs[0]->get_ray = scene->funcptrs.ray_get_ptr[shape];
	scene->objs[0]->get_point = scene->funcptrs.point_get_ptr[shape];
	return (0);
}
