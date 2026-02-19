/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_rt.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 14:31:06 by rgohrig           #+#    #+#             */
/*   Updated: 2026/02/16 16:30:54 by rgohrig          ###   ########.fr       */
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
# include <fcntl.h>

# include "MLX42.h"
# include "libft.h"
# include "ft_printf.h"
# include "get_next_line.h"

#include "dynamic_array.h"
# include "structs.h"

#ifndef M_PI
	# define M_PI		3.14159265358979323846	/* pi */
#endif


// colors         rgba in memory
# define BLUE_256  ((t_color_256){.value = 0xFFFF0000})
# define BLAKE_256 ((t_color_256){.a = 255})
# define WHITE_256 ((t_color_256){.r = 255, .g = 255, .b = 255, .a = 255})

#define BLACK_VEC3 ((t_vec3){0.0, 0.0, 0.0})
#define WHITE_VEC3 ((t_vec3){1.0, 1.0, 1.0})

# define BPP 4 // bytes per pixel
# define WIDTH_DEFAULT 800
# define HEIGHT_DEFAULT 600

# define DEBUG_RT 1 // 0 = off, 1 = on

// auto
t_vec3		ray_to_color(const t_ray *ray, int depth);
void		img_fill_256(mlx_image_t *img, const t_color_256 *color);
void		img_copy(mlx_image_t *change, mlx_image_t *source);
void		img_white_to_black(mlx_image_t *change);
void		swap_screen_imgs(t_gui *gui);
void		img_draw_vec3(uint8_t* pixel, const t_vec3 *color_linear);
void		img_draw_256(uint8_t* pixel, const t_color_256 *color);
bool		scatter_lambertian(const t_norm_ray* hit, t_ray *scattered);
bool		scatter_metal(const t_ray* r_in, const t_norm_ray* hit, t_ray *scattered, const t_material *material);
double		reflectance(double cosine, double refraction_idx);
bool		scatter_dielectric(const t_ray* r_in, const t_norm_ray *hit, t_ray *scattered, double ri);
bool		pars_atof_converted(char const **str_pos, double *num);
bool		pars_comma_skipped(char const **str_pos);
bool		pars_atoi_converted(const char **str_pos, int *result);
bool		pars_ambient_light(t_scene *scene, const char **line);
bool		pars_camera(t_scene *scene, const char **line);
bool		pars_light(t_scene *scene, const char **line);
bool		pars_sphere(t_scene *scene, const char **line);
bool		pars_plane(t_scene *scene, const char **line);
bool		pars_cylinder(t_scene *scene, const char **line);
void		free_gui(t_gui *gui);
void		free_scene(t_scene *scene);
void		free_data(void);
void		render(void);
void		loop_rays(mlx_image_t *img, t_camera *camera);
void		sample_rays(uint32_t x, uint32_t y, mlx_image_t *img, t_camera *camera);
t_vec3		get_pix_pos_base(t_camera *camera, uint32_t x, uint32_t y);
t_ray		final_ray(const t_vec3 *base, t_camera *camera);
int			get_time_ms(struct timeval *anchor);
long		get_time_us(struct timeval *anchor);
double		get_time_s(struct timeval *anchor);
void		reset_render_time(t_gui *gui);
void		draw_stats(const char *string, t_gui *gui);
void		update_stats(t_gui *gui, t_camera *camera);
void		init_gui(t_gui *gui);
void		program_exit(int exit_code);
void		perror_exit(const char *msg);
void		msg_exit(const char *msg);
void		msg_2_exit(const char *msg, const char *msg2);
void		perror_mlx_exit(const char *msg);
void		hook_main(void *gui_void);
void		init_hooks(t_gui *gui);
void		hook_key(mlx_key_data_t key_data, void *gui_void);
void		hook_resize(int32_t width, int32_t height, void *gui_void);
bool		pars_coordinate_converted(const char **line_pos, t_vec3 *result);
bool		pars_coordinate_interval_converted(const char **line_pos, t_vec3 *result, t_interval range);
bool		pars_double_in_range_converted(const char **line_pos, double *result, t_interval range);
bool		pars_int8_in_range_converted(const char **line_pos, uint8_t *result);
bool		pars_color_256_converted(const char **line_pos, t_color_256 *result_color);
bool		pars_color_vec3_converted(const char **line_pos, t_vec3 *result_color);
bool		parse_line(t_scene *scene, const char **line_pos);
int			init_scene(t_scene *scene, int argc, char const *argv[]);
void		purple_spheres(t_scene *scene);
void		init_sphere(t_scene *scene);
void		test_fov(t_scene *scene);
void		init_camera(mlx_image_t *img, t_camera *camera);
int			main(int argc, char const *argv[]);
void		test_r3(void);
void		test_random(void);
void		test_dynamic_array(void);
int			test_caller(int argc, char const *argv[]);
void		debug_vec3(const char *msg, const t_vec3 *v);
void		debug_ray(const char *msg, const t_ray *ray);
void		debug_decimal(const char *msg, double d);
void		debug_material(const t_material *material);
void		debug_sphere(const t_sphere *sph);
t_vec3		add_vec3(t_vec3 a, const t_vec3 b);
t_vec3		sub_vec3(t_vec3 a, const t_vec3 b);
t_vec3		mul_vec3(t_vec3 a, const t_vec3 b);
t_vec3		div_vec3(t_vec3 a, const t_vec3 b);
t_vec3		add_one_vec3(t_vec3 a, const double add);
t_vec3		sub_one_vec3(t_vec3 a, const double subtract);
t_vec3		mul_one_vec3(t_vec3 a, const double multiply);
t_vec3		div_one_vec3(t_vec3 a, const double divide);
double		combine_vec3(const t_vec3 a);
double		dot_vec3(const t_vec3 a, const t_vec3 b);
double		length_squared_vec3(const t_vec3 a);
double		length_vec3(const t_vec3 a);
t_vec3		inverse_vec3(const t_vec3 a);
t_vec3		square_vec3(const t_vec3 a);
t_vec3		cross_vec3(const t_vec3 a, const t_vec3 b);
t_vec3		fabs_vec3(const t_vec3 *a);
t_vec3		normalize_vec3(const t_vec3 a);
t_vec3		get_pos_on_ray(const t_ray *ray, const double length);
t_vec3		reflect_vec3(const t_vec3 vector, const t_vec3 normal);
t_vec3		refract_vec3(const t_vec3* unit_vector, const t_vec3 *normal, double etai_over_etat);
bool		is_interval_in(const t_interval interval, const double value);
bool		is_bigger_vec3(const t_vec3 val, const t_vec3 against);
bool		is_interval_in_vec3(const t_vec3 value, const t_vec3 min, const t_vec3 max);
bool		is_near_zero(const double value);
bool		is_near_zero_vec3(const t_vec3 a);
void		add_vec3_p(t_vec3 *a, const t_vec3 b);
void		sub_vec3_p(t_vec3 *a, const t_vec3 b);
void		mul_vec3_p(t_vec3 *a, const t_vec3 b);
void		div_vec3_p(t_vec3 *a, const t_vec3 b);
void		add_one_vec3_p(t_vec3 *a, const double add);
void		sub_one_vec3_p(t_vec3 *a, const double subtract);
void		mul_one_vec3_p(t_vec3 *a, const double multiply);
void		div_one_vec3_p(t_vec3 *a, const double divide);
double		degrees_to_radians(const double degrees);
double		linear_to_gamma(const double linear_color_part);
void		color_256_to_vec3(t_color_256 *in, t_vec3 *out);
bool		is_hit_sphere(const t_sphere *sph, const t_ray *ray, const t_interval ray_boarder, t_norm_ray *hit);
t_vec3		get_random_on_hemisphere(const t_vec3 *hit_direction_normal);
t_dynamic_array		dynamic_array_init(size_t element_size);
void		dynamic_array_add_back(t_dynamic_array *array, const void *item);
void		*dynamic_array_get(t_dynamic_array *array, size_t idx);
void		dynamic_array_free(t_dynamic_array *array);
void		ft_realloc(void **change_ptr, size_t old, size_t new, size_t size);
void		ft_realloc_2(void **change_first, void **change_last, size_t *elements_count, size_t size);
t_data		*get_data(void);
t_gui		*get_gui(void);
t_scene		*get_scene(void);
double		get_random();
t_vec3		get_random_vec3();
t_vec3		get_random_unit_vector();

#endif
