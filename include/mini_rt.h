/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_rt.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 14:31:06 by rgohrig           #+#    #+#             */
/*   Updated: 2026/02/09 18:07:00 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_RT_H
# define MINI_RT_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <math.h>
# include <limits.h>
# include <sys/time.h>

# include "MLX42.h"
# include "libft.h"
# include "ft_printf.h"

#include "dynamic_array.h"
# include "structs.h"

#ifndef M_PI
	# define M_PI		3.14159265358979323846	/* pi */
#endif


// colors         rgba in memory
# define BLUE  ((t_color_256){.value = 0xFFFF0000})
# define BLAKE ((t_color_256){.a = 255})
# define WHITE ((t_color_256){.r = 255, .g = 255, .b = 255, .a = 255})

# define BPP 4 // bytes per pixel
# define WIDTH_DEFAULT 800
# define HEIGHT_DEFAULT 600

# define DEBUG_RT 1 // 0 = off, 1 = on

// auto
t_dynamic_array		dynamic_array_init(size_t element_size);
void		dynamic_array_add_back(t_dynamic_array *array, const void *item);
void		*dynamic_array_get(t_dynamic_array *array, size_t idx);
void		dynamic_array_free(t_dynamic_array *array);
void		ft_realloc(void **change_ptr, size_t old, size_t new, size_t size);
void		ft_realloc_2(void **change_first, void **change_last, size_t *elements_count, size_t size);
t_vec3		add_vec3(t_vec3 a, const t_vec3 b);
t_vec3		sub_vec3(t_vec3 a, const t_vec3 b);
t_vec3		mul_vec3(t_vec3 a, const t_vec3 b);
t_vec3		div_vec3(t_vec3 a, const t_vec3 b);
t_vec3		add_vec3_one(t_vec3 a, const double add);
t_vec3		sub_vec3_one(t_vec3 a, const double subtract);
t_vec3		mul_vec3_one(t_vec3 a, const double multiply);
t_vec3		div_vec3_one(t_vec3 a, const double divide);
double		combine_vec3(const t_vec3 a);
double		dot_vec3(const t_vec3 a, const t_vec3 b);
double		length_squared_vec3(const t_vec3 a);
double		length_vec3(const t_vec3 a);
double		degrees_to_radians(const double degrees);
t_vec3		inverse_vec3(const t_vec3 a);
t_vec3		square_vec3(const t_vec3 a);
t_vec3		cross_vec3(const t_vec3 a, const t_vec3 b);
t_vec3		fabs_vec3(const t_vec3 *a);
t_vec3		normalize_vec3(const t_vec3 a);
t_vec3		get_pos_on_ray(const t_ray *ray, const double length);
t_vec3		reflect_vec3(const t_vec3 vector, const t_vec3 normal);
bool		is_hit_sphere(const t_sphere *sph, const t_ray *ray, const t_interval ray_boarder, t_norm_ray *hit);
t_vec3		get_random_on_hemisphere(const t_vec3 *hit_direction_normal);
bool		is_interval_in(const t_interval interval, const double value);
double		get_random();
t_vec3		get_random_vec3();
t_vec3		get_random_unit_vector();
bool		is_bigger_vec3(const t_vec3 val, const t_vec3 against);
bool		is_interval_in_vec3(const t_vec3 value, const t_vec3 min, const t_vec3 max);
bool		is_near_zero(const double value);
bool		is_near_zero_vec3(const t_vec3 a);
bool		scatter_lambertian(const t_norm_ray* hit, t_ray *scattered);
bool		scatter_metal(const t_ray* r_in, const t_norm_ray* hit, t_ray *scattered);
t_vec3		ray_to_color(const t_ray *ray, int depth);
void		img_fill_256(mlx_image_t *img, const t_color_256 *color);
void		img_copy(mlx_image_t *change, mlx_image_t *source);
void		swap_screen_imgs(t_gui *gui);
void		img_draw_vec3(uint8_t* pixel, const t_vec3 *color_linear);
void		img_draw_256(uint8_t* pixel, const t_color_256 *color);
double		linear_to_gamma(const double linear_color_part);
int			fr_atof(char const *str, double *num);
void		program_exit(int exit_code);
void		perror_exit(const char *msg);
void		msg_exit(const char *msg);
void		perror_mlx_exit(const char *msg);
void		hook_main(void *gui_void);
void		init_hooks(t_gui *gui);
void		hook_key(mlx_key_data_t key_data, void *gui_void);
void		hook_resize(int32_t width, int32_t height, void *gui_void);
t_data		*get_data(void);
t_gui		*get_gui(void);
t_scene		*get_scene(void);
void		free_gui(t_gui *gui);
void		free_scene(t_scene *scene);
void		free_data(void);
int			init_scene(t_scene *scene, int argc, char const *argv[]);
t_camera		*init_camera(mlx_image_t *img);
void		init_gui(t_gui *gui);
void		get_ray_pix_center(mlx_image_t *img, t_camera *camera, uint32_t x, uint32_t y, t_ray *all);
void		fill_rays(mlx_image_t *img, t_camera *camera, t_ray *all);
void		render(void);
t_ray		offset_ray(t_ray *ray, t_camera *camera);
t_vec3		anti_alias(t_ray *ray, uint32_t total, t_camera *camera);
void		debug_vec3(const char *msg, const t_vec3 *v);
void		debug_ray(const char *msg, const t_ray *ray);
void		debug_decimal(const char *msg, double d);
int			main(int argc, char const *argv[]);
void		test_r3(void);
void		test_random(void);
void		test_dynamic_array(void);
int			test_caller(int argc, char const *argv[]);

#endif
