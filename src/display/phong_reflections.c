/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong_reflections.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pantoine <pantoine@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 22:33:54 by pantoine          #+#    #+#             */
/*   Updated: 2024/11/14 12:11:35 by pantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "compute.h"

static t_vector	get_halfway_vector(t_point point, t_light source, t_ray ray)
{
	t_vector	halfway_vec;
	t_vector	view_vec;
	t_vector	light_direction;

	light_direction = vector_operation(source.origin, point, substract);
	view_vec = vector_scalar_operation(ray.direction, -1, multiply);
	halfway_vec = vector_operation(light_direction, view_vec, add);
	return (normalise(halfway_vec));
}

static t_colour	prevent_colour_overflow(t_colour extra_light,
				t_light source, float reflection)
{
	if (!reflection)
		return (extra_light);
	if (extra_light.r + reflection * source.colour.r > 255)
		extra_light.r = 255;
	else
		extra_light.r += reflection * source.colour.r;
	if (extra_light.g + reflection * source.colour.g > 255)
		extra_light.g = 255;
	else
		extra_light.g += reflection * source.colour.g;
	if (extra_light.b + reflection * source.colour.b > 255)
		extra_light.b = 255;
	else
		extra_light.b += reflection * source.colour.b;
	return (extra_light);
}

static float	get_specular_coef(t_object obj,
					t_point point, t_light light, t_ray ray)
{
	t_vector	halfway_vec;
	t_vector	normal;

	normal = obj.get_normal_vec(point, &obj);
	halfway_vec = get_halfway_vector(point, light, ray);
	return (obj.specular_coef * powf(dot(normal, halfway_vec), obj.shininess));
}

t_colour	get_specular_shading(t_scene scene, t_object *obj,
				t_ray ray, t_point point)
{
	t_colour		extra_light;
	float			specular_intensity;
	unsigned int	i;

	i = 0;
	specular_intensity = 0;
	extra_light = (t_colour){0, 0, 0};
	while (i < scene.light_sources.nb_lights)
	{
		if (!path_to_light(scene.objs,
				&scene.light_sources.source[i++], point))
			continue ;
		i--;
		specular_intensity = get_specular_coef(*obj,
				point, scene.light_sources.source[i], ray);
		extra_light = prevent_colour_overflow(extra_light,
				scene.light_sources.source[i++], specular_intensity);
	}
	return (extra_light);
}
