/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colour_operations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pantoine <pantoine@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 22:00:47 by pantoine          #+#    #+#             */
/*   Updated: 2024/11/14 12:06:24 by pantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shapes.h"
#include <math.h>

t_colour	combine_all_lights(t_colourblend *cb, t_object *object)
{
	t_colour	result;

	result.r = fmin((1 - object->reflection_coef)
			* (cb->s.r + cb->d.r + cb->a.r)
			+ object->reflection_coef * cb->r.r, 255);
	result.g = fmin((1 - object->reflection_coef)
			* (cb->s.g + cb->d.g + cb->a.g)
			+ object->reflection_coef * cb->r.g, 255);
	result.b = fmin((1 - object->reflection_coef)
			* (cb->s.b + cb->d.b + cb->a.b)
			+ object->reflection_coef * cb->r.b, 255);
	return (result);
}

int	rgb_to_int(t_colour colour)
{
	int	int_colour;

	int_colour = colour.r;
	int_colour = (int_colour << 8) | colour.g;
	int_colour = (int_colour << 8) | colour.b;
	return (int_colour);
}
