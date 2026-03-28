/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ileon <ileon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 11:03:36 by rgohrig           #+#    #+#             */
/*   Updated: 2026/03/28 10:48:10 by ileon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

static void	fill_random_buckets(int *testing)
{
	double	result;
	int		bucket;
	int		i;

	i = 0;
	while (i < 1000000)
	{
		result = get_random();
		if (result < 0.0 || result >= 1.0)
		{
			printf("Error: random out of bounds: %f\n", result);
			exit(1);
		}
		bucket = (int)(result * 10);
		testing[bucket]++;
		i++;
	}
}

void	test_r3(void)
{
	t_vec3	v3;
	int		i;

	i = 0;
	while (i < 10000000)
	{
		v3 = get_random_unit_vector();
		printf("_lengt:_%f\n", length_vec3(v3));
		(void)v3;
		i++;
	}
}

void	test_random(void)
{
	int	testing[10];
	int	i;

	ft_bzero(testing, sizeof(testing));
	fill_random_buckets(testing);
	printf("Results after 1,000,000 iterations:\n");
	i = 0;
	while (i < 10)
	{
		printf("Range %i: %d\n", i, testing[i]);
		i++;
	}
}

void	test_dynamic_array(void)
{
	t_dynamic_array	ar;
	double			*head;

	ar = dynamic_array_init_exit(sizeof(double));
	dynamic_array_add_back_exit(&ar, &(double){0});
	dynamic_array_add_back_exit(&ar, &(double){1});
	dynamic_array_add_back_exit(&ar, &(double){2});
	dynamic_array_add_back_exit(&ar, &(double){3});
	dynamic_array_add_back_exit(&ar, &(double){4});
	dynamic_array_add_back_exit(&ar, &(double){5});
	dynamic_array_add_back_exit(&ar, &(double){6});
	dynamic_array_add_back_exit(&ar, &(double){7});
	dynamic_array_add_back_exit(&ar, &(double){8});
	dynamic_array_add_back_exit(&ar, &(double){9});
	dynamic_array_add_back_exit(&ar, &(double){10});
	dynamic_array_add_back_exit(&ar, &(double){11});
	head = ar.first;
	while (head != ar.last)
	{
		printf("value: %.2f\n", *head);
		head++;
	}
	dynamic_array_free(&ar);
}
