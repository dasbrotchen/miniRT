/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_camera.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgrangeo <rgrangeo@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 23:46:44 by rgrangeo          #+#    #+#             */
/*   Updated: 2024/11/14 12:14:58 by pantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "compute.h"

int	create_camera(char **line, t_camera *camera)
{
	int		error;

	error = 2;
	if (nbr_parameters(line) != 4)
		return (putstr_error("Enter the right number of parameters"));
	if (parse_vector(&camera->viewpoint, line[1], &error) == ERROR)
		return (ERROR);
	if (parse_normalise_vectors(&camera->direction, line[2], &error) == ERROR)
		return (ERROR);
	camera->fov = str_fov(line[3], &error);
	if (error != 2)
		return (ERROR);
	return (NONE);
}
