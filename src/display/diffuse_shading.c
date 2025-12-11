/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   diffuse_shading.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pantoine <pantoine@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 20:17:53 by pantoine          #+#    #+#             */
/*   Updated: 2024/11/14 12:11:18 by pantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "compute.h"

static t_vector	add_source_diffuse(t_object obj, t_light source,
					t_vector diffuse_curr, float normal_angle)
{
	t_vector	extra_diffuse;

	extra_diffuse.x = diffuse_curr.x + obj.diffuse_coef
		* (source.colour.r / 255.0f)
		* source.brightness * normal_angle;
	extra_diffuse.y = diffuse_curr.y + obj.diffuse_coef
		* (source.colour.g / 255.0f)
		* source.brightness * normal_angle;
	extra_diffuse.z = diffuse_curr.z + obj.diffuse_coef
		* (source.colour.b / 255.0f)
		* source.brightness * normal_angle;
	return (extra_diffuse);
}

static t_colour	compute_final_diffuse_colour(t_object *obj,
					t_vector diff_intensity, t_point point)
{
	t_colour	diffuse_colour;
	t_colour	obj_c;

	obj_c = obj->get_colour(obj, point);
	diffuse_colour.r = fmin(obj_c.r,
			fmax(0, diff_intensity.x * obj_c.r));
	diffuse_colour.g = fmin(obj_c.g,
			fmax(0, diff_intensity.y * obj_c.g));
	diffuse_colour.b = fmin(obj_c.b,
			fmax(0, diff_intensity.z * obj_c.b));
	return (diffuse_colour);
}

/*
* This has to be called after get_specular_shading,
* since it assumes the values for blocked lights were already
* set. This enables us to skip multiple path_to_light calls.
*/
t_colour	get_diffuse_shading(t_scene scene, t_object *obj, t_point point)
{
	t_vector		diffuse_intensity;
	t_vector		normal_vec;
	unsigned int	i;
	t_light			curr_light;

	i = 0;
	if (!obj->diffuse_coef)
		return ((t_colour){0, 0, 0});
	normal_vec = obj->get_normal_vec(point, obj);
	diffuse_intensity = (t_vector){0, 0, 0};
	while (i < scene.light_sources.nb_lights)
	{
		if (scene.light_sources.source[i++].is_blocked)
			continue ;
		i--;
		curr_light = scene.light_sources.source[i];
		diffuse_intensity = add_source_diffuse(*obj,
				curr_light, diffuse_intensity,
				get_light_intensity(normal_vec, curr_light, point));
		i++;
	}
	return (compute_final_diffuse_colour(obj, diffuse_intensity, point));
}
