/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pantoine <pantoine@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 10:31:21 by pantoine          #+#    #+#             */
/*   Updated: 2024/11/14 12:10:08 by pantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "compute.h"

static void	get_neighbours_colours(t_colour *neighbours,
					t_bumpmap *bm, float *texels)
{
	neighbours[0] = colour_at_point(bm, texels[1], texels[0]);
	neighbours[1] = colour_at_point(bm, texels[1], texels[2]);
	neighbours[2] = colour_at_point(bm, texels[3], texels[0]);
	neighbours[3] = colour_at_point(bm, texels[3], texels[2]);
}

/*
* Horizontal and vertical interpolations are applied at the 
* same time. 
*
*	  0									0
*	  |									|
*0 -> colours[0]------f[0](h0)---colours[1] -> 1
*     |                   |				|
*     |					  |				|
*     |					  |				|
*     |					  |				|
*     f[1]----------------o-----------f[1]
*     |					  |				|
*     |					  |				|
*1 -> colours[2]------f[0](h1)---colours[3]-> 1
*	  |								    |
*	  0								    1
*
* This follows the exact same logic as for bumps in 
* get_filtered_height, we are simply applying it to each colour
* channel.
*/
static t_colour	apply_colour_interpolations(t_colour *colours, float *fractions)
{
	t_colour	colour;

	colour.r = (colours[0].r * (1 - fractions[0])
			+ colours[2].r * fractions[0]) * (1 - fractions[1])
		+ (colours[1].r * (1 - fractions[0]) + colours[3].r * fractions[0])
		* fractions[1];
	colour.g = (colours[0].g * (1 - fractions[0])
			+ colours[2].g * fractions[0]) * (1 - fractions[1])
		+ (colours[1].g * (1 - fractions[0]) + colours[3].g * fractions[0])
		* fractions[1];
	colour.b = (colours[0].b * (1 - fractions[0])
			+ colours[2].b * fractions[0]) * (1 - fractions[1])
		+ (colours[1].b * (1 - fractions[0]) + colours[3].b * fractions[0])
		* fractions[1];
	return (colour);
}

/*
* Bilinear filtering again:
*
*	  0									0
*	  |									|
*0 -> (t[0], t[1])------f[0](h0)---(t[2], t[1]) -> 1
*     |                   |				|
*     |					  |				|
*     |					  |				|
*     |					  |				|
*     f[1]----------------o-----------f[1]
*     |					  |				|
*     |					  |				|
*1 -> (t[0], t[3])------f[0](h1)---(t[2], t[3]) -> 1
*	  |								    |
*	  0								    1
*
* colours[0] here stores the colour of the pixel,
* basically the same as neighbour[0] in get_filtered_height
*
*/
t_colour	get_filtered_colour(t_bumpmap *bump_map, float u, float v)
{
	float		raw_texels[2];
	float		texels[4];
	float		fractions[2];
	t_colour	colours[4];

	raw_texels[0] = u * (bump_map->width - 1);
	raw_texels[1] = v * (bump_map->height - 1);
	texels[0] = (int)floorf(raw_texels[0]);
	texels[1] = (int)floorf(raw_texels[1]);
	texels[2] = get_wrapped_coord(texels[0] + 1, bump_map->width);
	texels[3] = get_wrapped_coord(texels[1] + 1, bump_map->height);
	texels[0] = get_wrapped_coord(texels[0], bump_map->width);
	texels[1] = get_wrapped_coord(texels[1], bump_map->height);
	fractions[0] = raw_texels[0] - floorf(raw_texels[0]);
	fractions[1] = raw_texels[1] - floorf(raw_texels[1]);
	get_neighbours_colours(colours, bump_map, texels);
	return (apply_colour_interpolations(colours, fractions));
}
