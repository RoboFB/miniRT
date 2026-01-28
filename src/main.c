/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 13:25:10 by rgohrig           #+#    #+#             */
/*   Updated: 2026/01/28 15:02:52 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

// plane
	// t_plane plane;
	// plane.color.r = 000;
	// plane.color.g = 200;
	// plane.color.b = 0;
	// plane.color.a = 255;
	// plane.orientation.x = 0.0;
	// plane.orientation.y = 1.0;
	// plane.orientation.z = 0.0;
	// plane.position.x = 0.0;
	// plane.position.y = -1.0;
	// plane.position.z = 5.0;

void test(void)
{
	t_camera * cam = &get_data()->camera;
	cam->fov = 90.0;
	
	cam->position.x = 0.0;
	cam->position.y = 0.0;
	cam->position.z = 0.0;
	
	cam->orientation.x = 0.0;
	cam->orientation.y = 0.0;
	cam->orientation.z = 0.0;

	
	// t_vec3 directions[WIDTH_DEFAULT * HEIGHT_DEFAULT];
	double scale = tan(cam->fov * (M_PI / 180.0) * 0.5);
	printf("scale: %f\n", scale);
	// ft_bzero(buffer_array, sizeof(t_vec3) * WIDTH_DEFAULT * HEIGHT_DEFAULT);
	
	double imageAspectRatio = (double)WIDTH_DEFAULT / (double)HEIGHT_DEFAULT; // assuming width > height
	for (int y = 0; y < HEIGHT_DEFAULT; y++)
	{
		for (int x = 0; x < WIDTH_DEFAULT; x++)
		{
			// printf("Aspect Ratio: %f\n", imageAspectRatio);
			t_vec3 direction;
			direction.x = (-1.0 + (2.0 * ((x + 0.5) / (double)WIDTH_DEFAULT)) ) * scale * imageAspectRatio;
			direction.y = ( 1.0 - (2.0 * ((y + 0.5) / (double)HEIGHT_DEFAULT))) * scale;
			direction.z = 1.0;
			// directions[y * WIDTH_DEFAULT + x].x = (-1.0 + (2.0 * ((x + 0.5) / (double)WIDTH_DEFAULT)) ) * scale * imageAspectRatio;
			// directions[y * WIDTH_DEFAULT + x].y = ( 1.0 - (2.0 * ((y + 0.5) / (double)HEIGHT_DEFAULT))) * scale;
			// directions[y * WIDTH_DEFAULT + x].z = 1.0;

			t_ray ray;
			ray.origin = cam->position;
			ray.direction = direction;

			t_color_d color = ray_to_color(&ray);



			mlx_put_pixel(get_gui()->buffer_img, x, y, color_d_to_255(color).value);

			if ((x == 0 && y == 0) || (x == WIDTH_DEFAULT -1 && y == HEIGHT_DEFAULT -1))
			{
				print_vec3("directions", &direction);
			}
		}
	}
}

// Main function, starts the program
int	main(int argc, char const *argv[])
{
	t_gui	*gui;

	gui = get_gui();

	(void)argc;
	(void)argv;
	// parser(argc, argv);
	init_data(get_data());
	// fr_add_hooks(gui);
	
	test();

	update_screen(gui);
	mlx_loop(gui->mlx);

	// fr_free_all(gui);
	return (0);
}


