/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ileon <ileon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 12:06:53 by rgohrig           #+#    #+#             */
/*   Updated: 2026/03/28 12:13:34 by ileon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

/* Frees the pointer at the given address and sets it to NULL. */
void	free_helper(void *address_of_pointer_to_free)
{
	void	**cast_pointer;

	cast_pointer = (void **)address_of_pointer_to_free;
	if (cast_pointer && *cast_pointer)
	{
		free(*cast_pointer);
		*cast_pointer = NULL;
	}
}

/* Frees all MLX/GUI resources. */
void	free_gui(t_gui *gui)
{
	if (gui->mlx)
		mlx_terminate(gui->mlx);
	gui->mlx = NULL;
}

/* Frees all scene dynamic arrays (shapes, lights). */
void	free_scene(t_scene *scene)
{
	free_helper(&scene->camera);
	free_helper(&scene->ambient_light);
	dynamic_array_free(&scene->lights);
	dynamic_array_free(&scene->spheres);
	dynamic_array_free(&scene->planes);
	dynamic_array_free(&scene->cylinders);
}

/* Frees all global program data (scene and GUI). */
void	free_data(void)
{
	free_gui(&get_data()->gui);
	free_scene(&get_data()->scene);
}
