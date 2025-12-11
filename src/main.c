/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pantoine <pantoine@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 09:39:36 by pantoine          #+#    #+#             */
/*   Updated: 2024/11/14 18:06:32 by pantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "compute.h"
#include "parsing.h"

static int	close_window(t_scene *scene)
{
	mlx_destroy_image(scene->inst, scene->img.img_ptr);
	free_scene(scene);
	mlx_destroy_window(scene->inst, scene->window);
	mlx_destroy_display(scene->inst);
	free(scene->inst);
	printf("\nbye bye\n");
	exit(EXIT_SUCCESS);
	return (0);
}

static int	key_press(int keycode, t_scene *scene)
{
	if (keycode == 65307)
		close_window(scene);
	return (0);
}

static void	add_mlx_attributes(t_scene *scene)
{
	scene->window = mlx_new_window(scene->inst, WIDTH, HEIGHT, "miniRT");
	if (!scene->window)
	{
		free_scene(scene);
		mlx_destroy_display(scene->inst);
		free(scene->inst);
		putstr_error("Failed to create window");
		exit(EXIT_FAILURE);
	}
	scene->img.img_ptr = mlx_new_image(scene->inst, WIDTH, HEIGHT);
	if (!scene->img.img_ptr)
	{
		free_scene(scene);
		mlx_destroy_window(scene->inst, scene->window);
		mlx_destroy_display(scene->inst);
		free(scene->inst);
		putstr_error("Failed to create pixel buffer");
		exit(EXIT_FAILURE);
	}
	scene->img.img_pixels = mlx_get_data_addr(scene->img.img_ptr,
			&scene->img.bpp, &scene->img.size_line, &scene->img.endian);
	scene->camera = setup_camera(scene->camera);
}

int	main(int ac, char **av)
{
	t_scene				scene;

	if (ac != 2)
		return (putstr_error("Usage: ./miniRT <scene_name>"));
	scene.inst = mlx_init();
	if (!scene.inst)
	{
		putstr_error("Failed to init mlx");
		exit(EXIT_FAILURE);
	}
	init_function_ptrs(&scene);
	if (parsing(av[1], &scene) == ERROR)
	{
		mlx_destroy_display(scene.inst);
		free(scene.inst);
		return (1);
	}
	add_mlx_attributes(&scene);
	mlx_hook(scene.window, 17, 1L << 0, close_window, &scene);
	mlx_hook(scene.window, 2, 1L << 0, key_press, &scene);
	render_scene(scene);
	mlx_loop(scene.inst);
	return (0);
}
