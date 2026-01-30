/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_rt.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 14:31:06 by rgohrig           #+#    #+#             */
/*   Updated: 2026/01/30 17:42:39 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_RT_H
# define MINI_RT_H

# define _USE_GNU

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <math.h>


# include "MLX42.h"
# include "libft.h"
# include "ft_printf.h"

#include "dynamic_array.h"
# include "structs.h"

#ifndef M_PI
	# define M_PI		3.14159265358979323846	/* pi */
#endif

// colors         bgra
# define BLUE   0xFF0000FF
# define BLAKE 0x000000FF
# define WHITE 0xFFFFFFFF

# define BPP 4 // bytes per pixel
# define WIDTH_DEFAULT 800
# define HEIGHT_DEFAULT 600

# define DEBUG_RT 1 // 0 = off, 1 = on

// auto
void		render(void);
int			main(int argc, char const *argv[]);
void		test_dynamic_array();
int			test_caller(int argc, char const *argv[]);
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
t_vec3		vec3_inverse(t_vec3 a);
t_vec3		vec3_square(t_vec3 a);
t_vec3		vec3_cross(const t_vec3 a, const t_vec3 b);
double		vec3_combine(t_vec3 a);
double		vec3_dot(const t_vec3 a, const t_vec3 b);
double		vec3_length_squared(const t_vec3 a);
double		vec3_length(const t_vec3 a);
t_vec3		vec3_fabs(const t_vec3 *a);
t_vec3		vec3_normalize(t_vec3 a);
t_vec3		ray_get_pos(const t_ray *ray, double length);
double		degrees_to_radians(double degrees);
void		debug_vec3(const char *msg, const t_vec3 *v);
void		debug_ray(const char *msg, const t_ray *ray);
void		debug_decimal(const char *msg, double d);
t_data		*get_data(void);
t_gui		*get_gui(void);
t_color_d		vec3_to_color_d(const t_vec3 v);
void		hook_main(void *gui_void);
void		add_hooks(t_gui *gui);
void		hook_key(mlx_key_data_t key_data, void *gui_void);
t_color_d		ray_to_color(const t_ray *ray);
t_color_256		color_d_to_255(t_color_d color);
t_color_256		get_color_from_vec3(t_vec3 *rayDirection);
t_color_256		get_color_test(int x, int y);
bool		hit_sphere(const t_sphere *sph, const t_ray *ray, double ray_min, double ray_max, t_norm_ray *hit);
void		ft_realloc(void **change_ptr, size_t old, size_t new, size_t size);
void		ft_realloc_2(void **change_first, void **change_last, size_t *elements_count, size_t size);
t_dynamic_array		dynamic_array_init(size_t element_size);
void		dynamic_array_add_back(t_dynamic_array *array, const void *item);
void		*dynamic_array_get(t_dynamic_array *array, size_t idx);
void		dynamic_array_free(t_dynamic_array *array);
int			fr_atof(char const *str, double *num);
uint32_t		fr_get_rgba(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
bool		fr_color_cmp(uint8_t *pixel_color, uint32_t check_color);
bool		fr_pixel_cmp(mlx_image_t *img, t_pixel *pix, uint32_t check_color);

#endif
