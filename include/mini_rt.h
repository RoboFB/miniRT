/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_rt.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 14:31:06 by rgohrig           #+#    #+#             */
/*   Updated: 2026/01/27 20:10:04 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_RT_H
# define MINI_RT_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <math.h>

# define _USE_MATH_DEFINES

# include "MLX42.h"
# include "libft.h"
# include "ft_printf.h"

# include "structs.h"

# define BLAKE 0x000000FF
# define WHITE 0xFFFFFFFF

# define BPP 4 // bytes per pixel
# define WIDTH_DEFAULT 800
# define HEIGHT_DEFAULT 600

# define DEBUG_RT 1 // 0 = off, 1 = on

// auto
void		test(void);
int			main(int argc, char const *argv[]);
void		init_gui(t_gui *gui);
void		init_data(t_data *data);
void		program_exit(int exit_code);
void		perror_exit(const char *msg, int exit_code);
void		msg_exit(const char *msg);
void		img_fill_color(mlx_image_t *img, uint32_t color);
void		img_copy(mlx_image_t *change, mlx_image_t *source);
void		update_screen(t_gui *gui);
t_vec3		vec3_add(t_vec3 a, t_vec3 b);
t_vec3		vec3_sub(t_vec3 a, t_vec3 b);
t_vec3		vec3_mul(t_vec3 a, t_vec3 b);
t_vec3		vec3_div(t_vec3 a, t_vec3 b);
t_vec3		vec3_add_one(t_vec3 a, double add);
t_vec3		vec3_sub_one(t_vec3 a, double subtract);
t_vec3		vec3_mul_one(t_vec3 a, double multiply);
t_vec3		vec3_div_one(t_vec3 a, double divide);
t_vec3		vec3_square(t_vec3 a);
double		vec3_combine(t_vec3 a);
t_vec3		vec3_fabs(const t_vec3 *a);
t_vec3		ray_get_pos(const t_ray *ray, double t);
t_vec3		vec3_normalize(const t_vec3 *a);
void		print_vec3(const char *msg, const t_vec3 *v);
t_data		*get_data(void);
t_gui		*get_gui(void);
t_color_d		direction_to_color(const t_vec3 *direction);
t_color_256		color_d_to_255(t_color_d color);
t_color_256		get_color_from_vec3(t_vec3 *rayDirection);
t_color_256		get_color_test(int x, int y);

#endif
