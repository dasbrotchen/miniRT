/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_to_world.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pantoine <pantoine@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 22:43:54 by pantoine          #+#    #+#             */
/*   Updated: 2024/11/11 12:48:23 by pantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "camera.h"
#include "compute.h"

/*
 * direction.z set to 1, to ensure positive Z is always forward.
 */
static t_vector	get_world_direction_vector(t_camera camera,
					t_2dpoint normalised_point)
{
	t_vector	direction;

	direction.x = normalised_point.x;
	direction.y = normalised_point.y;
	direction.z = 1;
	direction = normalise(direction);
	direction = mat_vec_product(camera.inverse_camera, direction);
	return (direction);
}

static t_2dpoint	normalise_pixel(t_2dpoint point, t_camera camera)
{
	t_2dpoint	normalised;

	normalised.x = ((2 * point.x) / WIDTH) - 1;
	normalised.y = 1 - ((2 * point.y) / HEIGHT);
	normalised.y *= camera.screen_height;
	normalised.x *= camera.screen_width;
	return (normalised);
}

t_ray	pixel_to_ray(t_camera camera, t_2dpoint pixel)
{
	t_ray	ray;

	ray.origin.x = camera.viewpoint.x;
	ray.origin.y = camera.viewpoint.y;
	ray.origin.z = camera.viewpoint.z;
	ray.direction = get_world_direction_vector(camera,
			normalise_pixel(pixel, camera));
	return (ray);
}
