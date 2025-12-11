/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bump_maps.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pantoine <pantoine@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 19:11:54 by pantoine          #+#    #+#             */
/*   Updated: 2025/12/11 15:37:04 by pantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "compute.h"
#include "parsing.h"

static void	*xpm_file_read_error(char *filename)
{
	ft_putstr_fd("Error\nCould not read file `", 2);
	ft_putstr_fd(filename, 2);
	ft_putstr_fd("'\n", 2);
	return (NULL);
}

t_bumpmap	*load_bumpmap(void *inst, char *filename, t_bumpmap *bm)
{
	int			bpp;
	int			line_size;
	int			endian;

	bm->img_ptr = mlx_xpm_file_to_image(inst, filename,
			&bm->width, &bm->height);
	if (!bm->img_ptr)
		return (xpm_file_read_error(filename));
	bm->pixel_data = (int *)mlx_get_data_addr(bm->img_ptr,
			&bpp, &line_size, &endian);
	if (!bm->pixel_data)
	{
		putstr_error("Failed to fetch pixel data");
		mlx_destroy_image(inst, bm->img_ptr);
		return (NULL);
	}
	if (!ft_strncmp(filename, "assets/marble.xpm", 17))
		bm->zoom = 0.02f;
	else
		bm->zoom = 1;
	bm->depth = 0.01f;
	return (bm);
}

/*
* Bilinear filtering;
* raw_texels[0] and [1] are the pixel equivalent of uv on the texture.
* wrapped coordinates ensure we go back to the beginning
* once we reach the end of the texture.
* The aim of this '''graph''' is to show what's going on
* with this function, the idea is to sample the greyscale values
* around a uvpoint which does not necessarily falls in the middle
* of a pixel (as it is usually the case).
*
* t[0], t[1], t[2], t[3] are texels[x] in the function below.
* f[0], f[1] are fractions[x].
* neighbours[0] up to 3 are the greyscale (height) values
* at (t[0], t[1]), (t[2], t[1]) etc., as defined in 
* get_neighbours() (bump_maps_utils.c).
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
* Here, (h1) and (h0) are the horizontally interpolated values;
* point o is the final interpolation (vertical), and we find it in
* the return statement of this function: 
*	h0 * (1 - f[1]) + h1 * f[1]
*/
static float	get_filtered_height(t_bumpmap *bump_map, float u, float v)
{
	float	raw_texels[2];
	float	neighbours[4];
	float	texels[4];
	float	fractions[2];
	float	interpolated[2];

	raw_texels[0] = u * (bump_map->width - 1);
	raw_texels[1] = v * (bump_map->height - 1);
	texels[0] = (int)floorf(raw_texels[0]);
	texels[1] = (int)floorf(raw_texels[1]);
	texels[2] = get_wrapped_coord(texels[0] + 1, bump_map->width);
	texels[3] = get_wrapped_coord(texels[1] + 1, bump_map->height);
	texels[0] = get_wrapped_coord(texels[0], bump_map->width);
	texels[1] = get_wrapped_coord(texels[1], bump_map->height);
	fractions[0] = raw_texels[0] - floorf(texels[0]);
	fractions[1] = raw_texels[1] - floorf(texels[1]);
	get_neighbours(neighbours, bump_map, texels);
	interpolated[0] = neighbours[0] * (1 - fractions[0])
		+ neighbours[1] * fractions[0];
	interpolated[1] = neighbours[2] * (1 - fractions[0])
		+ neighbours[3] * fractions[0];
	return (interpolated[0] * (1 - fractions[1])
		+ interpolated[1] * fractions[1]);
}

/*
* The tangent will be {0, 0, 0} if we take the cross product of
* the same vector (everything cancels out), hence we choose the
* tangent based on the normal's y component.
*/
static t_vector	local_tangent(t_vector normal)
{
	if (fabsf(normal.y) < 1)
		return (normalise(x_prod((t_vector){0, 1, 0}, normal)));
	return (normalise(x_prod((t_vector){1, 0, 0}, normal)));
}

/*
* This bump normal function draws from the 'legit' formulas to get
* the bumped normal n' = (dq/dv) x (dq/du) where
* q(u,v) = p(u,v) + h(u,v)n(u,v). After some testing, we decided to use
* n' = (n - (tangent * dh(u,v)/du)) - (n - (bitangent * dh(u,v)/dv)).
* The bitangent is not explicitely assigned in the code, but it
* is x_prod(normal, tangent).
* The effective change is that we do not compute dp(u,v)/du and 
* dp(u,v)/dv because the resulting shading was too clear-cut,
* missing a 'fade'. This component of the bumped normal is unrelated to
* the 'bump' effect which is fully accounted for by the h(u,v)
* component, hence directly replacing it by the normal yields
* better results.
*/
t_vector	bump_normal(t_bumpmap *bump_map, t_2dpoint uvpoint,
			t_vector normal, float scale_factor)
{
	float		heights[3];
	float		dv;
	float		du;
	t_vector	tangent;
	t_vector	perturbed;

	heights[0] = get_filtered_height(bump_map, uvpoint.x, uvpoint.y);
	heights[1] = get_filtered_height(bump_map,
			uvpoint.x + 1.0f / bump_map->width, uvpoint.y);
	heights[2] = get_filtered_height(bump_map,
			uvpoint.x, uvpoint.y + 1.0f / bump_map->height);
	du = -(heights[1] - heights[0]) * scale_factor * bump_map->width;
	dv = -(heights[2] - heights[0]) * scale_factor * bump_map->height;
	tangent = local_tangent(normal);
	perturbed = normal;
	perturbed = vector_operation(perturbed,
			vector_scalar_operation(tangent, du, multiply), substract);
	perturbed = vector_operation(perturbed,
			vector_scalar_operation(x_prod(normal, tangent),
				dv, multiply), substract);
	return (normalise(perturbed));
}
