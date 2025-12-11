/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgrangeo <rgrangeo@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 16:02:23 by rgrangeo          #+#    #+#             */
/*   Updated: 2024/11/14 12:17:44 by pantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "compute.h"

int	parse_vector(t_vector *vector, char *line, int *error)
{
	char	**split;

	split = ft_split(line, ',');
	if (split == NULL)
		return (putstr_error("Malloc error"));
	if (nbr_parameters(split) != 3)
	{
		free_split(split);
		return (putstr_error("Enter the right number of parameters"));
	}
	vector->x = str_float(split[0], error);
	vector->y = str_float(split[1], error);
	vector->z = str_float(split[2], error);
	free_split(split);
	return (1);
}

int	parse_normalise_vectors(t_vector *vector, char *line, int *error)
{
	char	**split;

	split = ft_split(line, ',');
	if (split == NULL)
		return (putstr_error("Malloc error"));
	if (nbr_parameters(split) != 3)
	{
		free_split(split);
		return (putstr_error("Enter the right number of parameters"));
	}
	vector->x = str_float(split[0], error);
	vector->y = str_float(split[1], error);
	vector->z = str_float(split[2], error);
	free_split(split);
	if (*error == 2 && (vector->x < -1 || vector->x > 1
			|| vector->y < -1 || vector->y > 1
			|| vector->z < -1 || vector->z > 1))
		return (putstr_error("Enter values between -1 and 1 \
for normalised vectors"));
	*vector = normalise(*vector);
	return (1);
}

int	parse_colour(t_colour *colour, char *line, int *error)
{
	char	**split;

	split = ft_split(line, ',');
	if (split == NULL)
		return (putstr_error("Malloc error"));
	if (nbr_parameters(split) != 3)
	{
		free_split(split);
		return (putstr_error("Entering the right number of parameters"));
	}
	colour->r = str_colour(split[0], error);
	colour->g = str_colour(split[1], error);
	colour->b = str_colour(split[2], error);
	free_split(split);
	return (1);
}

void	set_lighting_intensities_dfl(t_object *object)
{
	object->shininess = 30;
	object->specular_coef = 1;
	object->diffuse_coef = 1;
	object->reflection_coef = 0;
}
