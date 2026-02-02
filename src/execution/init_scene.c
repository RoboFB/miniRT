/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 11:56:59 by rgohrig           #+#    #+#             */
/*   Updated: 2026/02/02 13:44:48 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "mini_rt.h"



// R: 0 = success, else error
int init_scene(t_scene *scene, int argc, char const *argv[])
{
	// TODO: implement parsing here.
	(void)argc;
	(void)argv;

	scene->camera = init_camera();

	scene->all_rays = ft_calloc(get_gui()->img->width * get_gui()->img->height, sizeof(t_ray));// todo: implement null check


	
	return (0);
}


t_camera	*init_camera(void)
{
	t_camera	*camera;

	camera = ft_calloc(1, sizeof(t_camera));// todo: implement null check
	camera->position = (t_vec3){0.0, 0.0, 0.0};
	camera->orientation = (t_vec3){0.0, 0.0, 0.0};
	camera->fov = 90.0;

	return (camera);
}

