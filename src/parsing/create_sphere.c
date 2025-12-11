/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_sphere.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgrangeo <rgrangeo@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 02:52:32 by rgrangeo          #+#    #+#             */
/*   Updated: 2024/11/14 17:40:57 by pantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "compute.h"

static t_sphere	*filling_sphere(char **line, int *error,
					int type, t_object *obj)
{
	t_sphere	*sphere;
	void		*texture;

	texture = NULL;
	obj->has_img = 0;
	sphere = malloc(sizeof(t_sphere));
	if (sphere == NULL)
		return (putstr_malloc_error());
	if (malloc_texture(type, (void *)sphere, &texture))
		return (NULL);
	obj->texture = texture;
	if (parse_vector(&sphere->centre,
			line[1 + 1 * (type != NORMAL)], error) == ERROR)
		return (object_filler_error(sphere, obj->texture, NULL));
	sphere->radius = str_float(line[2 + 1 * (type != NORMAL)], error) * 0.5f;
	if (sphere->radius <= 0)
		return (object_filler_error(sphere, obj->texture, "Diameter must\
 be positive"));
	return (sphere);
}

static int	set_sphere_properties(char **line, t_scene *scene,
				int *error, int type)
{
	if (type == NORMAL)
	{
		if (parse_colour(&scene->objs[0]->colour,
				line[SP_MIN_ARGS - 1], error) == ERROR)
			return (ERROR);
		if (parse_lighting_intensities(scene->objs[0],
				line + SP_MIN_ARGS, error) == ERROR)
			return (ERROR);
	}
	if (load_textures(type, scene, line + SP_MIN_ARGS, line[1]))
		return (ERROR);
	if (parse_textured_lighting_intensities(line + SP_MIN_ARGS,
			error, scene, type))
		return (ERROR);
	return (OBJECT);
}

int	create_sphere(char **line, t_scene *scene)
{
	t_sphere	*sphere;
	int			error;
	int			type;

	error = 2;
	set_lighting_intensities_dfl(scene->objs[0]);
	type = type_object(line[1]);
	if (object_valid_n_params(type, nbr_parameters(line), SP_MIN_ARGS))
		return (putstr_error("Enter the right number of parameters"));
	sphere = filling_sphere(line, &error, type, scene->objs[0]);
	if (sphere == NULL)
		return (ERROR);
	scene->objs[0]->object = (void *)sphere;
	if (set_sphere_properties(line, scene, &error, type) == ERROR)
		return (ERROR);
	scene->objs[0]->intersect = &get_sphere_intersections;
	if (assign_function_ptrs(type, scene, line, SPHERE))
		return (ERROR);
	scene->objs[0]->distance = -1;
	if (error != 2)
	{
		free(scene->objs[0]->texture);
		return (putstr_error("Unable to read value"));
	}
	return (OBJECT);
}
