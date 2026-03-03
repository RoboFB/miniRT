/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 13:25:10 by rgohrig           #+#    #+#             */
/*   Updated: 2026/03/03 18:26:34 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

// Main function, starts the program
int	main(int argc, char const *argv[])
{
	t_gui	*gui;
	t_scene	*scene;

	// for debugging tests
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
