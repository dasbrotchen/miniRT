/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colours.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pantoine <pantoine@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 16:54:55 by pantoine          #+#    #+#             */
/*   Updated: 2024/11/13 23:09:28 by pantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOURS_H
# define COLOURS_H
# include "ray.h"
# include "shapes.h"

struct	s_object;
struct	s_sources;
struct	s_light;
struct	s_colour;
struct	s_colourblend;
struct	s_scene;
struct	s_checkerboard;
struct	s_bumpmap;
struct	s_2dpoint;
struct	s_cylinder;
struct	s_sphere;
struct	s_plane;
struct	s_cone;

/*
 * UV mapping
*/
//checkerboards
struct s_checkerboard	*create_checkerboard(unsigned int w,
							unsigned int h, struct s_colour a,
							struct s_colour b);
struct s_colour			get_checkered_plane_colour(struct s_object *obj,
							t_point point);
struct s_colour			get_checkered_sphere_colour(struct s_object *obj,
							t_point point);
struct s_colour			get_checkered_cylinder_colour(struct s_object *obj,
							t_point point);
struct s_colour			get_checkered_cone_colour(struct s_object *obj,
							t_point point);
struct s_colour			colour_from_uv(t_2dpoint uvpoint,
							struct s_checkerboard checkers);
struct s_2dpoint		sphere_point_to_uv_direction(t_point point,
							struct s_sphere sphere, float zoom);
struct s_2dpoint		sphere_point_to_uv_point(t_point point,
							struct s_sphere sphere, float zoom);
struct s_2dpoint		plane_point_to_uv(t_point point, float scale_factor);
struct s_2dpoint		plane_point_to_uv_textures(t_point point,
							struct s_plane plane, float scale);
struct s_2dpoint		uv_cap(t_point point, t_point cap_center, float radius);
struct s_2dpoint		cylinder_point_to_uv(t_point point,
							struct s_cylinder cylinder);
struct s_2dpoint		cone_point_to_uv(t_point point,
							struct s_cone cone);
struct s_2dpoint		cone_point_to_uv_checkers(t_point point,
							struct s_cone cone);

//bumpmaps, image textures
struct s_bumpmap		*load_bumpmap(void *inst, char *filename,
							struct s_bumpmap *bm);
t_vector				bump_normal(struct s_bumpmap *bump_map,
							struct s_2dpoint uvpoint, t_vector normal,
							float scale_factor);
struct s_colour			get_sphere_img_colour(struct s_object *obj,
							t_point point);
struct s_colour			get_plane_img_colour(struct s_object *obj,
							t_point point);
struct s_colour			get_cylinder_img_colour(struct s_object *obj,
							t_point point);
struct s_colour			get_cone_img_colour(struct s_object *obj,
							t_point point);
struct s_colour			get_filtered_colour(struct s_bumpmap *bump_map,
							float u, float v);
struct s_colour			checkered_colour_from_uv(struct s_2dpoint uvpoint,
							struct s_checkerboard checkers);
int						get_wrapped_coord(int coord, int max);
//bumpmaps, utils
void					get_neighbours(float *neighbours,
							struct s_bumpmap *bm, float *texels);
//textures
struct s_colour			colour_at_point(struct s_bumpmap *bm,
							int i1, int i2);
struct s_colour			int_to_rgb(int colour);
struct s_colour			get_object_colour(struct s_object *obj,
							t_point point);
int						rgb_to_int(struct s_colour colour);
struct s_colour			combine_all_lights(struct s_colourblend *cb,
							struct s_object *object);
float					get_light_intensity(t_vector normal,
							struct s_light source, t_point point);
struct s_colour			get_reflected_light(struct s_scene scene,
							t_ray ray, struct s_object *obj, t_point point);
struct s_colour			get_diffuse_shading(struct s_scene scene,
							struct s_object *obj, t_point point);
struct s_colour			get_specular_shading(struct s_scene scene,
							struct s_object *obj, t_ray ray, t_point point);
struct s_colour			get_ambient_shading(struct s_light ambient_light,
							struct s_object *obj, t_point point);
int						path_to_light(struct s_object **objs,
							struct s_light *source, t_point point);

#endif
