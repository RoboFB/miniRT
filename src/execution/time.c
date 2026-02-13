/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 15:17:05 by rgohrig           #+#    #+#             */
/*   Updated: 2026/02/13 21:04:47 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

int	get_time_ms(struct timeval *anchor)
{
	struct timeval	curr;

	gettimeofday(&curr, NULL);
	return ((curr.tv_sec - anchor->tv_sec) * 1000
		+ (curr.tv_usec - anchor->tv_usec) / 1000);
}

long	get_time_us(struct timeval *anchor)
{
	struct timeval	curr;

	gettimeofday(&curr, NULL);
	return ((curr.tv_sec - anchor->tv_sec) * 1000 * 1000
		+ (curr.tv_usec - anchor->tv_usec));
}


void	bench_time(int state, mlx_t *mlx, t_camera *camera, mlx_image_t *img)
{
	static struct timeval	start_time;
	static int				mode = 0;
	static mlx_image_t		*str_img;
	static mlx_image_t		*img_back;

	if (state == 0)
	{
		gettimeofday(&start_time, NULL);
	}
	else
	{
		if (mode == 0)
		{
			
			char *str_time = ft_itoa(get_time_us(&start_time));
			char *str_ray = ft_itoa((camera->anti_aliasing_samples *img->width *img->height));
			if (str_time == NULL || str_ray == NULL)
			{
				free(str_time);
				free(str_ray);
				return;
			}
			char *full_str = ft_strjoin_4("rays: ", str_ray, " render time: ", str_time);
			free(str_time);
			free(str_ray);
			if (full_str == NULL)
			{
				return;
			}

			if (str_img != NULL)
				mlx_delete_image(mlx, str_img);
			if (img_back != NULL)
				mlx_delete_image(mlx, img_back);
			
			str_img = mlx_put_string(mlx, full_str, 10, 10);
			img_back = mlx_new_image(mlx, str_img->width, str_img->height);
			img_fill_256(img_back, &(t_color_256){.r = 0, .g = 200, .b = 0, .a = 100});
			mlx_image_to_window(mlx, img_back, 10, 10);
			mlx_set_instance_depth(img_back->instances, 2);
			mlx_set_instance_depth(str_img->instances, 3);
			printf(" img:%d back:%d, str_img:%d\n", img->instances->z, img_back->instances->z, str_img->instances->z);
			
			free(full_str);
		}
	}
	// printf(" img:%d \n", img->instances->z);
}

