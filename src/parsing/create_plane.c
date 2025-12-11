/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_plane.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgrangeo <rgrangeo@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 21:13:54 by rgrangeo          #+#    #+#             */
/*   Updated: 2024/11/14 17:41:14 by pantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "parsing.h"
#include "compute.h"

static t_plane	*filling_plane(char **line, int *error, int type, t_object *obj)
{
	t_plane	*plane;
	void	*texture;

	texture = NULL;
	obj->has_img = 0;
	plane = malloc(sizeof(t_plane));
	if (plane == NULL)
		return (putstr_malloc_error());
	if (malloc_texture(type, (void *)plane, &texture))
		return (NULL);
	obj->texture = texture;
	if (parse_vector(&plane->position,
			line[1 + 1 * (type != NORMAL)], error) == ERROR)
		return (object_filler_error(plane, obj->texture, NULL));
	if (parse_normalise_vectors(&plane->normal,
			line[2 + 1 * (type != NORMAL)], error) == ERROR)
		return (object_filler_error(plane, obj->texture, NULL));
	return (plane);
}

static int	set_plane_properties(char **line, t_scene *scene,
				int *error, int type)
{
	if (type == NORMAL)
	{
		if (parse_colour(&scene->objs[0]->colour,
				line[PL_MIN_ARGS - 1], error) == ERROR)
			return (ERROR);
		if (parse_lighting_intensities(scene->objs[0],
				line + PL_MIN_ARGS, error) == ERROR)
			return (ERROR);
	}
	if (load_textures(type, scene, line + PL_MIN_ARGS, line[1]))
		return (ERROR);
	if (parse_textured_lighting_intensities(line + PL_MIN_ARGS,
			error, scene, type))
		return (ERROR);
	return (OBJECT);
}

/*
* minimum number of parameters for a plane: 4.
*/
int	create_plane(char **line, t_scene *scene)
{
	t_plane	*plane;
	int		error;
	int		type;

	error = 2;
	set_lighting_intensities_dfl(scene->objs[0]);
	type = type_object(line[1]);
	if (object_valid_n_params(type, nbr_parameters(line), PL_MIN_ARGS))
		return (putstr_error("Enter the right number of parameters"));
	plane = filling_plane(line, &error, type, scene->objs[0]);
	if (plane == NULL)
		return (ERROR);
	scene->objs[0]->object = (void *)plane;
	if (set_plane_properties(line, scene, &error, type) == ERROR)
		return (ERROR);
	scene->objs[0]->intersect = &get_plane_intersection;
	if (assign_function_ptrs(type, scene, line, PLANE))
		return (ERROR);
	scene->objs[0]->distance = -1;
	if (error != 2)
		return (putstr_error("Unable to read value"));
	return (OBJECT);
}
