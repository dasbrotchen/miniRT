/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pantoine <pantoine@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 18:08:44 by pantoine          #+#    #+#             */
/*   Updated: 2024/11/14 15:40:29 by rgrangeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "compute.h"
#include "mlx.h"

/*
* Fill the pixel buffer with the corresponding colour. Here 'p' refers
* to a pixel.
*/
static inline void	add_to_img(t_img *img, t_2dpoint p,
						t_colourblend *cb, t_object *obj)
{
	((int *)img->img_pixels)[(int)p.y
		* (img->size_line >> 2) + (int)p.x] = \
			rgb_to_int(combine_all_lights(cb, obj));
}

/*
* Fill the colourblend, which is pretty much just the combination
* of all lights received on a pixel.
*/
static inline t_colourblend	get_colourblend(t_scene scene, t_object *obj,
								t_ray ray, t_point point)
{
	return ((t_colourblend){.s = get_specular_shading(scene, obj, ray, point),
		.d = get_diffuse_shading(scene, obj, point),
		.a = get_ambient_shading(scene.ambient, obj, point),
		.r = get_reflected_light(scene, ray, obj, point)});
}

/*
* The 'brain' of the raytracer. We transalate a pixel on the screen
* to a ray from the camera's pov to that pixel in cartesian coords.
* We then find the closest object, i.e. the one we will have
* to display on the screen. Then, given the object and the intersection
* point, we compute the 4 lighting 'channels' in get_colourblend:
* specular, diffuse, ambient, and reflective. They are added together
* according the the coefficients specified in input (or the default
* ones). Finally, we assign that colour to the coordinate in the image
* with add_to_img.
*/
static inline void	store_colour(t_scene scene, t_2dpoint p)
{
	t_ray			ray;
	t_point			point;
	t_object		*closest;
	t_colourblend	pixel_colour;

	ray = pixel_to_ray(scene.camera, p);
	closest = first_hit_object(scene.objs, ray, &point);
	if (closest)
	{
		pixel_colour = get_colourblend(scene, closest, ray, point);
		add_to_img(&scene.img, p, &pixel_colour, closest);
	}
}

/*
* Two loops to iterate over each pixel of the screen, compute
* the color at each pixel, store it, and then display the whole
* buffer at once.
*/
void	render_scene(t_scene scene)
{
	t_2dpoint		pixel;
	int				i;
	int				j;

	i = 0;
	j = 0;
	while (i <= WIDTH - 1)
	{
		while (j <= HEIGHT - 1)
		{
			pixel.x = i;
			pixel.y = j++;
			store_colour(scene, pixel);
		}
		progress_bar(i, WIDTH - 1);
		i++;
		j = 0;
	}
	mlx_put_image_to_window(scene.inst, scene.window, scene.img.img_ptr, 0, 0);
}
