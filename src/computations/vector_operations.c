/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_operations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pantoine <pantoine@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 18:51:38 by pantoine          #+#    #+#             */
/*   Updated: 2024/11/14 12:09:32 by pantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "compute.h"

t_vector	normalise(t_vector vec)
{
	float		norm;

	norm = sqrt(sqrf(vec.x) + sqrf(vec.y) + sqrf(vec.z));
	return (vector_scalar_operation(vec, norm, divide));
}

t_vector	vector_operation(t_vector v1, t_vector v2,
				float (*f)(float n1, float n2))
{
	t_vector	result;

	result.x = f(v1.x, v2.x);
	result.y = f(v1.y, v2.y);
	result.z = f(v1.z, v2.z);
	return (result);
}
