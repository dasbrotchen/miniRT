/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cylinder.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgrangeo <rgrangeo@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 21:13:49 by rgrangeo          #+#    #+#             */
/*   Updated: 2024/11/14 17:40:22 by pantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "compute.h"

static inline void	fill_cylinder_params(t_cylinder *cylinder)
{
	cylinder->rot_quaternion = construct_quaternion(cylinder->axis);
	cylinder->minz = cylinder->centre.z - (cylinder->height * 0.5);
	cylinder->maxz = cylinder->centre.z + (cylinder->height * 0.5);
}

static t_cylinder	*filling_cylinder(char **line, int *error,
						int type, t_object *obj)
{
	t_cylinder	*cylinder;
	void		*texture;

	texture = NULL;
	obj->has_img = 0;
	cylinder = malloc(sizeof(t_cylinder));
	if (cylinder == NULL)
		return (putstr_malloc_error());
	if (malloc_texture(type, (void *)cylinder, &texture))
		return (NULL);
	obj->texture = texture;
	if (parse_vector(&cylinder->centre, line[1 + 1 * (type != NORMAL)], \
			error) == ERROR)
		return (object_filler_error(cylinder, obj->texture, NULL));
	if (parse_vector(&cylinder->axis, line[2 + 1 * (type != NORMAL)], \
			error) == ERROR)
		return (object_filler_error(cylinder, obj->texture, NULL));
	cylinder->radius = str_float(line[3 + 1 * (type != NORMAL)], error) * 0.5f;
	if (cylinder->radius <= 0)
		return (object_filler_error(cylinder, obj->texture, "Diameter < 0"));
	cylinder->height = str_float(line[4 + 1 * (type != NORMAL)], error);
	if (cylinder->height <= 0)
		return (object_filler_error(cylinder, obj->texture, "Height negative"));
	fill_cylinder_params(cylinder);
	return (cylinder);
}

static int	set_cylinder_properties(char **line, t_scene *scene,
				int *error, int type)
{
	if (type == NORMAL)
	{
		if (parse_colour(&scene->objs[0]->colour,
				line[CY_MIN_ARGS - 1], error) == ERROR)
			return (ERROR);
		if (parse_lighting_intensities(scene->objs[0],
				line + CY_MIN_ARGS, error) == ERROR)
			return (ERROR);
	}
	if (load_textures(type, scene, line + CY_MIN_ARGS, line[1]))
		return (ERROR);
	if (parse_textured_lighting_intensities(line + CY_MIN_ARGS,
			error, scene, type))
		return (ERROR);
	return (OBJECT);
}

/*
* minimum number of parameters for a cylinder: 4.
*/
int	create_cylinder(char **line, t_scene *scene)
{
	t_cylinder	*cylinder;
	int			error;
	int			type;

	error = 2;
	set_lighting_intensities_dfl(scene->objs[0]);
	type = type_object(line[1]);
	if (object_valid_n_params(type, nbr_parameters(line), CY_MIN_ARGS))
		return (putstr_error("Enter the right number of parameters"));
	cylinder = filling_cylinder(line, &error, type, scene->objs[0]);
	if (cylinder == NULL)
		return (ERROR);
	scene->objs[0]->object = (void *)cylinder;
	if (set_cylinder_properties(line, scene, &error, type) == ERROR)
		return (ERROR);
	scene->objs[0]->intersect = &get_cylinder_intersections;
	if (assign_function_ptrs(type, scene, line, CYLINDER))
		return (ERROR);
	scene->objs[0]->distance = -1;
	if (error != 2)
		return (putstr_error("Unable to read value"));
	return (OBJECT);
}
