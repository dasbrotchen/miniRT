/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_tools_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgrangeo <rgrangeo@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 14:35:59 by rgrangeo          #+#    #+#             */
/*   Updated: 2024/11/14 17:31:31 by pantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "compute.h"

int	parse_lighting_intensities(t_object *object, char **line, int *error)
{
	while (*line)
	{
		if (!ft_strncmp(*line, "shi=", 4))
			object->shininess = str_float(*line + 4, error);
		else if (!ft_strncmp(*line, "spe=", 4))
			object->specular_coef = str_float(*line + 4, error);
		else if (!ft_strncmp(*line, "dif=", 4))
			object->diffuse_coef = str_float(*line + 4, error);
		else if (!ft_strncmp(*line, "ref=", 4))
			object->reflection_coef = str_float(*line + 4, error);
		else
			return (putstr_error("Unknown parameter encountered"));
		line += 1;
	}
	if (object->shininess < 0)
		return (putstr_error("Shininess values must not be negative"));
	if ((object->specular_coef < 0 || object->specular_coef > 1)
		|| (object->reflection_coef < 0 || object->reflection_coef > 1)
		|| (object->diffuse_coef < 0 || object->diffuse_coef > 1))
		return (putstr_error("Specular and reflection must be \
between 1 and 0"));
	return (0);
}

static int	load_checkered_textures(char **line, t_scene *scene, int *error)
{
	t_checkerboard	*checkers;

	checkers = (t_checkerboard *)scene->objs[0]->texture;
	checkers->width = str_float(line[0], error);
	if (checkers->width < 1)
	{
		putstr_error("Pattern width must be at least 1");
		return (1);
	}
	checkers->height = str_float(line[1], error);
	if (checkers->height < 1)
	{
		putstr_error("Pattern height must be at least 1");
		return (1);
	}
	if (parse_colour(&checkers->a, line[2], error) == ERROR)
		return (1);
	if (parse_colour(&checkers->b, line[3], error) == ERROR)
		return (1);
	return (0);
}

static int	load_bump_textures(char *filename, t_scene *scene)
{
	t_bumpmap	*bm;

	bm = (t_bumpmap *)scene->objs[0]->texture;
	bm = load_bumpmap(scene->inst, ft_strchr(filename, '=') + 1, bm);
	if (!bm)
		return (ERROR);
	scene->objs[0]->has_img = 1;
	return (0);
}

int	load_textures(int type, t_scene *scene, char **line, char *filename)
{
	int			error;

	error = 2;
	if (type == CHECKERED)
	{
		if (load_checkered_textures(line, scene, &error))
			return (1);
	}
	else if (type == TEXTURED)
	{
		if (load_bump_textures(filename, scene))
			return (1);
	}
	else
		scene->objs[0]->has_img = 0;
	if (error != 2)
		return (1);
	return (0);
}

int	malloc_texture(int type, void *obj, void **texture)
{
	if (type == CHECKERED)
	{
		*texture = malloc(sizeof(t_checkerboard));
		if (!*texture)
		{
			free(obj);
			return (putstr_error("Malloc error"));
		}
	}
	else if (type == TEXTURED)
	{
		*texture = malloc(sizeof(t_bumpmap));
		if (!*texture)
		{
			free(obj);
			return (putstr_error("Malloc error"));
		}
	}
	else
		*texture = NULL;
	return (0);
}
