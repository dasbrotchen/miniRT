/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_light.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgrangeo <rgrangeo@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 22:39:43 by rgrangeo          #+#    #+#             */
/*   Updated: 2024/11/14 12:15:18 by pantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "compute.h"

int	create_light(char **line, t_light *light)
{
	int	error;

	error = 2;
	if (nbr_parameters(line) < 4)
		return (putstr_error("Enter the right number of parameters for light"));
	if (parse_vector(&light->origin, line[1], &error) == ERROR)
		return (ERROR);
	light->brightness = str_float(line[2], &error);
	if (light->brightness < 0 || light->brightness > 1)
		return (putstr_error("Enter a value between 0 and 1\
for light brightness"));
	if (parse_colour(&light->colour, line[3], &error) == ERROR)
		return (ERROR);
	if (error != 2)
		return (ERROR);
	return (LIGHT);
}

int	create_ambient_lightning(char **line, t_light *ambient)
{
	int	error;

	error = 2;
	if (nbr_parameters(line) != 3)
		return (putstr_error("Enter the right number of\
 parameters for ambient lighting"));
	ambient->brightness = str_float(line[1], &error);
	if (ambient->brightness < 0 || ambient->brightness > 1)
		return (putstr_error("Enter a value between 0 and 1\
 for Ambient lighting brightness"));
	if (parse_colour(&ambient->colour, line[2], &error) == ERROR)
		return (ERROR);
	if (error != 2)
		return (ERROR);
	return (NONE);
}
