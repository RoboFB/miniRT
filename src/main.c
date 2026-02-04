/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 13:25:10 by rgohrig           #+#    #+#             */
/*   Updated: 2026/02/04 15:28:20 by rgohrig          ###   ########.fr       */
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

	gui = &get_data()->gui;
	init_gui(gui);

	scene = &get_data()->scene;
	
	if (init_scene(scene, argc, argv) != 0)
		msg_exit("Parsing error occurred");
	render();
	mlx_loop(gui->mlx);
	free_data();
	return (0);
}












// dirty testing for random number generator
void test_random(void)
{
	double	result;

	int testing[10] = {0};

	for (int i = 0; i < 1000000; i++)
	{
		result = get_random();
		printf("random: %f\n", result);
		if (result >= 0.0 && result < 0.1)
			testing[0]++;
		else if (result >= 0.1 && result < 0.2)
			testing[1]++;
		else if (result >= 0.2 && result < 0.3)
			testing[2]++;
		else if (result >= 0.3 && result < 0.4)
			testing[3]++;
		else if (result >= 0.4 && result < 0.5)
			testing[4]++;
		else if (result >= 0.5 && result < 0.6)
			testing[5]++;
		else if (result >= 0.6 && result < 0.7)
			testing[6]++;
		else if (result >= 0.7 && result < 0.8)
			testing[7]++;
		else if (result >= 0.8 && result < 0.9)
			testing[8]++;
		else if (result >= 0.9 && result < 1.0)
			testing[9]++;
		else
		{
			printf("Error: random number out of bounds: %f\n", result);
			exit(1);
		}
	}
	printf("Results after 1,000,000 iterations:\n");
	for (int i = 0; i < 10; i++)
	{
		printf("Range %i: %d\n", i, testing[i]);
	}
}

void test_dynamic_array(void)
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
			if (ft_strncmp(argv[2], "random", 7) == 0)
			{
				test_random();
				return (1);
			}
		}
	}
	return (0);
}