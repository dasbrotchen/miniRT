/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world_to_camera_coords.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pantoine <pantoine@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 11:58:30 by pantoine          #+#    #+#             */
/*   Updated: 2024/11/13 23:03:34 by pantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "camera.h"
#include "compute.h"

static t_matrix	create_inverse_camera_matrix(t_camera camera)
{
	t_matrix	camera_matrix;

	camera_matrix.r1[0] = camera.right.x;
	camera_matrix.r1[1] = camera.right.y;
	camera_matrix.r1[2] = camera.right.z;
	camera_matrix.r2[0] = camera.up.x;
	camera_matrix.r2[1] = camera.up.y;
	camera_matrix.r2[2] = camera.up.z;
	camera_matrix.r3[0] = camera.direction.x;
	camera_matrix.r3[1] = camera.direction.y;
	camera_matrix.r3[2] = camera.direction.z;
	return (transpose(camera_matrix));
}

static void	set_dimension_settings(t_camera *camera)
{
	camera->radian_fov = camera->fov * (M_PI / 180);
	camera->screen_height = 1 * (tanf(camera->radian_fov * 0.5f));
	camera->screen_width = camera->screen_height
		* ((float)WIDTH / (float)HEIGHT);
	camera->inverse_camera = create_inverse_camera_matrix(*camera);
}

/*
	* If camera axis is (0, 0, 1), set upvec.y = 1.
	* If camera axis is (0, 1, 0), set upvec.z = 1.
	* If camera axis is (1, 0, 0), the upvector remains y.
	* camera direction NEEDS to be normalised.
*/
t_camera	setup_camera(t_camera camera)
{
	t_vector	upvec;

	upvec.x = 0;
	if (fabs(camera.direction.y) < 1)
	{
		upvec.y = 1;
		upvec.z = 0;
	}
	else
	{
		upvec.y = 0;
		upvec.z = 1;
	}
	camera.right = x_prod(upvec, camera.direction);
	camera.up = x_prod(camera.direction, camera.right);
	set_dimension_settings(&camera);
	return (camera);
}
