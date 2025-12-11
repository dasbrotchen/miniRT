/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cone.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgrangeo <rgrangeo@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 13:52:01 by rgrangeo          #+#    #+#             */
/*   Updated: 2024/11/14 17:43:23 by pantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "compute.h"

static inline void	fill_cone_params(t_cone *cone)
{
	cone->rot_quaternion = construct_quaternion(cone->axis);
	cone->minz = -(cone->height * 0.5);
	cone->maxz = (cone->height * 0.5);
}

static t_cone	*fill_cone_positions(char **line, int *error,
					int type, t_object *obj)
{
	t_cone	*cone;
	void	*texture;

	texture = NULL;
	obj->has_img = 0;
	cone = malloc(sizeof(t_cone));
	if (cone == NULL)
		return (putstr_malloc_error());
	if (malloc_texture(type, (void *)cone, &texture))
		return (NULL);
	obj->texture = texture;
	if (parse_vector(&cone->apex, line[1 + 1 * (type != NORMAL)], \
			error) == ERROR)
		return (object_filler_error(cone, obj->texture, NULL));
	if (parse_vector(&cone->axis, line[2 + 1 * (type != NORMAL)], \
			error) == ERROR)
		return (object_filler_error(cone, obj->texture, NULL));
	cone->height = str_float(line[3 + 1 * (type != NORMAL)], error) * 2;
	if (cone->height <= 0)
		return (object_filler_error(cone, obj->texture, "Height negative"));
	fill_cone_params(cone);
	cone->theta = str_float(line[4 + 1 * (type != NORMAL)], error);
	if (cone->theta <= 0)
		return (object_filler_error(cone, obj->texture, "Theta negative"));
	return (cone);
}

static int	set_cone_properties(char **line, t_scene *scene,
				int *error, int type)
{
	if (type == NORMAL)
	{
		if (parse_colour(&scene->objs[0]->colour,
				line[CO_MIN_ARGS - 1], error) == ERROR)
			return (ERROR);
		if (parse_lighting_intensities(scene->objs[0],
				line + CO_MIN_ARGS, error) == ERROR)
			return (ERROR);
	}
	if (load_textures(type, scene, line + CO_MIN_ARGS, line[1]))
		return (ERROR);
	if (parse_textured_lighting_intensities(line + CO_MIN_ARGS,
			error, scene, type))
		return (ERROR);
	return (OBJECT);
}

/*
* minimum number of parameters for a cone: 4.
*/
int	create_cone(char **line, t_scene *scene)
{
	t_cone	*cone;
	int		error;
	int		type;

	error = 2;
	set_lighting_intensities_dfl(scene->objs[0]);
	type = type_object(line[1]);
	if (object_valid_n_params(type, nbr_parameters(line), CO_MIN_ARGS))
		return (putstr_error("Enter the right number of parameters"));
	cone = fill_cone_positions(line, &error, type, scene->objs[0]);
	if (cone == NULL)
		return (ERROR);
	scene->objs[0]->object = (void *)cone;
	if (set_cone_properties(line, scene, &error, type) == ERROR)
		return (ERROR);
	scene->objs[0]->intersect = &get_cone_intersections;
	if (assign_function_ptrs(type, scene, line, CONE))
		return (ERROR);
	scene->objs[0]->distance = -1;
	if (error != 2)
		return (putstr_error("Unable to read value"));
	return (OBJECT);
}
