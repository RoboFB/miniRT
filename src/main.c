/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 13:25:10 by rgohrig           #+#    #+#             */
/*   Updated: 2026/01/30 20:54:26 by rgohrig          ###   ########.fr       */
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

void render(void)
{
	t_data *data = get_data();
	t_camera * cam = &data->camera;
	mlx_image_t *img = data->gui.buffer_img;
	cam->fov = 90.0;
	
	cam->position.x = 0.0;
	cam->position.y = 0.0;
	cam->position.z = 0.0;
	
	cam->orientation.x = 0.0;
	cam->orientation.y = 0.0;
	cam->orientation.z = 0.0;

	
	t_ray *all = malloc(WIDTH_DEFAULT * HEIGHT_DEFAULT * sizeof(t_ray));
	// ft_bzero(directions, sizeof(t_vec3) * WIDTH_DEFAULT * HEIGHT_DEFAULT);
	
	
	double scale = tan(degrees_to_radians(cam->fov) * 0.5);
	double imageAspectRatio = (double)img->width / (double)img->height; // assuming width > height
	for (uint32_t y = 0; y < img->height; y++)
	{
		for (uint32_t x = 0; x < img->width; x++)
		{
			t_vec3 direction;
			direction.x = (-1.0 + (2.0 * ((x + 0.5) / (double)img->width)) ) * scale * imageAspectRatio;
			direction.y = ( 1.0 - (2.0 * ((y + 0.5) / (double)img->height))) * scale;
			direction.z = -1.0;

			all[x + y * img->width].origin = cam->position;
			all[x + y * img->width].direction = direction;
		}
	}

	for (uint32_t y = 0; y < img->height; y++)
	{
		for (uint32_t x = 0; x < img->width; x++)
		{
			t_color_d color = ray_to_color(&all[x + y * img->width]);
			mlx_put_pixel(get_gui()->buffer_img, x, y, color_d_to_255(color).value);
		}
	}



}

// Main function, starts the program
int	main(int argc, char const *argv[])
{
	t_gui	*gui;

	gui = get_gui();


	if (test_caller(argc, argv))

		return (0);

	// parser(argc, argv);
	init_data(get_data());
	add_hooks(gui);

	render();
	update_screen(gui);

	// mlx_close_window(gui->mlx);

	mlx_loop(gui->mlx);

	// fr_free_all(gui);
	return (0);
}

void test_dynamic_array()
{
	t_dynamic_array ar;

	ar = dynamic_array_init(sizeof(double));

	double *head = ar.first;


	dynamic_array_add_back(&ar, &(double){0});
	dynamic_array_add_back(&ar, &(double){1});
	dynamic_array_add_back(&ar, &(double){2});
	dynamic_array_add_back(&ar, &(double){3});
	dynamic_array_add_back(&ar, &(double){4});
	dynamic_array_add_back(&ar, &(double){5});
	dynamic_array_add_back(&ar, &(double){6});
	dynamic_array_add_back(&ar, &(double){7});
	dynamic_array_add_back(&ar, &(double){8});
	dynamic_array_add_back(&ar, &(double){9});
	dynamic_array_add_back(&ar, &(double){10});
	dynamic_array_add_back(&ar, &(double){11});

	head = ar.first;
	while (head != ar.last)
	{
		/* code */
		printf("value: %.2f\n", *head);
		head++;
	}
	
	printf("\n");
	uint32_t idx = 0;
	while (idx < ar.elements_used)
	{
		double *current = dynamic_array_get(&ar, idx);
		/* code */


		printf("value: %.2f\n", *current);
		idx++;
	}


	dynamic_array_free(&ar);
}


int test_caller(int argc, char const *argv[])
{
	if (argc == 3)
	{
		if (ft_strncmp(argv[1], "-t", 3) == 0 
		|| ft_strncmp(argv[1], "--test", 7) == 0)
		{
			if (ft_strncmp(argv[2], "dynamic_array", 15) == 0)
			{
				test_dynamic_array();
				return (1);
			}
		}
	}
	return (0);
}