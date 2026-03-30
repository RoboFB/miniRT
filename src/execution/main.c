/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ileon <ileon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 13:25:10 by rgohrig           #+#    #+#             */
/*   Updated: 2026/03/28 12:12:55 by ileon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

/* Entry point: parses scene, initializes GUI, starts the render loop. */
int	main(int argc, char const *argv[])
{
	t_gui	*gui;
	t_scene	*scene;

	if (test_caller(argc, argv))
		return (0);
	gui = get_gui();
	init_gui_exit(gui);
	scene = get_scene();
	init_scene_exit(scene);
	pars_scene_exit(scene, argc, argv);
	calculate_camera(get_gui()->img, scene->camera);
	render();
	mlx_loop(gui->mlx);
	program_exit(EXIT_SUCCESS);
	return (EXIT_FAILURE);
}
