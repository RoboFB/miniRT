/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 12:06:53 by rgohrig           #+#    #+#             */
/*   Updated: 2026/02/02 12:17:39 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	free_gui(t_gui *gui)
{
	if (gui->mlx)
		mlx_terminate(gui->mlx);
	gui->mlx = NULL;
}

void	free_scene(t_scene *scene)
{
	free(scene->camera);
	scene->camera = NULL;
	free(scene->light);
	scene->light = NULL;
	free(scene->all_rays);
	scene->all_rays = NULL;

}

void	free_data(void)
{
	t_scene *scene;
	t_gui *gui;

	gui = &get_data()->gui;
	scene = &get_data()->scene;

	free_gui(gui);
	free_scene(scene);
}
