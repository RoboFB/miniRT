/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   statistics.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 14:37:03 by rgohrig           #+#    #+#             */
/*   Updated: 2026/03/05 16:20:58 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	draw_stats(const char *string, t_gui *gui)
{
	mlx_t			*mlx = gui->mlx;
	t_statistics	*stats = &gui->statistics;

	stats->str_img = mlx_put_string(mlx, string, 10, 10);
	stats->background_img = mlx_new_image(mlx, stats->str_img->width, stats->str_img->height);
	img_fill_256(stats->background_img, &(t_color_256){.r = 0, .g = 200, .b = 0, .a = 100});
	if (mlx_image_to_window(mlx, stats->background_img, 10, 10) < 0)
		perror_mlx_exit("Graphics: Image to Window failed");

	mlx_set_instance_depth(stats->background_img->instances, 2);
	mlx_set_instance_depth(stats->str_img->instances, 3);
}

void	try_delete_stats(mlx_t *mlx, mlx_image_t **img_1, mlx_image_t **img_2)
{
	if (*img_1 != NULL)
	{
		mlx_delete_image(mlx, *img_1);
		*img_1 = NULL;
	}
	if (*img_2 != NULL)
	{
		mlx_delete_image(mlx, *img_2);
		*img_2 = NULL;
	}
}

void	update_stats(t_gui *gui, t_camera *camera)
{
	t_statistics	*stats = &gui->statistics;
	mlx_image_t		*img = gui->img;

	char			final_string[64];
	try_delete_stats(gui->mlx, &stats->str_img, &stats->background_img);

	if (stats->type == STATS_RAYS_SEC)
	{
		double time_s = get_time_s(&stats->time_before_render);
		double total_rays = (camera->anti_aliasing_samples * img->width * img->height);
		double rays_sec = total_rays / time_s;

		ft_strlcpy(final_string, "rays/sec: ", 64);
		ft_strlcat(final_string, ft_itoa_static((int)rays_sec), 64);

		draw_stats(final_string, gui);
		
	}
}
