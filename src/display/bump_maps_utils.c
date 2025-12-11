/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bump_maps_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pantoine <pantoine@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 21:24:31 by pantoine          #+#    #+#             */
/*   Updated: 2024/11/14 12:11:05 by pantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "compute.h"

/*
* Analogous to int_to_rgb, but here we're interested
* in the greyscale instead of the actual pixel colour.
*/
static float	get_bump_height(int pixel)
{
	int	r;
	int	g;
	int	b;

	r = (pixel >> 16) & 0xFF;
	g = (pixel >> 8) & 0xFF;
	b = pixel & 0xFF;
	return (((r + g + b) / 3.0) / 255.0);
}

/*
* Negative coords are close to the max
* coords above the max are close to the beginning of the map
*/
int	get_wrapped_coord(int coord, int max)
{
	while (coord < 0)
		coord += max;
	while (coord >= max)
		coord -= max;
	return (coord);
}

static float	height_at_point(t_bumpmap *bm, int i1, int i2)
{
	return (get_bump_height(bm->pixel_data[i1 * bm->width + i2]));
}

void	get_neighbours(float *neighbours,
				t_bumpmap *bm, float *texels)
{
	neighbours[0] = height_at_point(bm, texels[1], texels[0]);
	neighbours[1] = height_at_point(bm, texels[1], texels[2]);
	neighbours[2] = height_at_point(bm, texels[3], texels[0]);
	neighbours[3] = height_at_point(bm, texels[3], texels[2]);
}
