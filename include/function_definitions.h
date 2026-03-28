/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function_definitions.h                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 14:31:06 by rgohrig           #+#    #+#             */
/*   Updated: 2026/03/06 16:00:03 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTION_DEFINITIONS_H
# define FUNCTION_DEFINITIONS_H
// start
t_vec3			ray_to_color(const t_ray *ray, int depth);
t_vec3			background_color(const t_ray *ray);
t_vec3			outside_the_obj(const t_material *material,
					const t_norm_ray *hit, const t_ray *ray, int depth);
t_vec3			inside_the_obj(const t_material *material, t_norm_ray *hit,
					const t_ray *ray, int depth);
t_vec3			phone_color(const t_material *material, const t_norm_ray *hit,
					const t_ray *ray);
void			img_draw_vec3(uint8_t *pixel, const t_vec3 *color_linear);
void			img_draw_256(uint8_t *pixel, const t_color_256 *color);
void			img_fill_256(mlx_image_t *img, const t_color_256 *color);
void			img_copy(mlx_image_t *change, mlx_image_t *source);
void			img_white_to_black(mlx_image_t *change);
void			swap_screen_imgs(t_gui *gui);
bool			scatter_lambertian(const t_norm_ray *hit, t_ray *scattered);
bool			scatter_metal(const t_ray *r_in, const t_norm_ray *hit,
					t_ray *scattered, const t_material *material);
double			reflectance(double cosine, double refraction_idx);
bool			scatter_dielectric(const t_ray *r_in, const t_norm_ray *hit,
					t_ray *scattered, double ri);
bool			is_in_shadow(const t_norm_ray *hit, const t_light *light);
void			*calloc_perror(size_t count, size_t size);
void			*calloc_perror_exit(size_t count, size_t size);
void			ft_realloc_perror(void **change_ptr, size_t old, size_t new,
					size_t size);
int				ft_realloc_perror_2(void **change_first, void **change_last,
					size_t *elements_count, size_t size);
t_dynamic_array	dynamic_array_init_exit(size_t element_size);
void			dynamic_array_add_back_exit(t_dynamic_array *array,
					const void *item);
int				dynamic_array_add_back_perror(t_dynamic_array *array,
					const void *item);
void			*dynamic_array_get(t_dynamic_array *array, size_t idx);
void			*dynamic_array_get_last(t_dynamic_array *array);
void			*dynamic_array_get_first(t_dynamic_array *array);
void			dynamic_array_free(t_dynamic_array *array);
t_data			*get_data(void);
t_gui			*get_gui(void);
t_scene			*get_scene(void);
double			get_random(void);
t_vec3			get_random_vec3(void);
t_vec3			get_random_unit_vector(void);
void			program_exit(int exit_code);
void			perror_exit(const char *msg);
void			msg_exit(const char *msg);
void			msg_2_exit(const char *msg, const char *msg2);
void			perror_mlx_exit(const char *msg);
void			free_helper(void *address_of_pointer_to_free);
void			free_gui(t_gui *gui);
void			free_scene(t_scene *scene);
void			free_data(void);
void			init_hooks(t_gui *gui);
void			hook_key(mlx_key_data_t key_data, void *gui_void);
void			move_camera_pos(mlx_key_data_t key_data, t_gui *gui,
					t_camera *camera);
void			move_camera_ang(mlx_key_data_t key_data, t_gui *gui,
					t_camera *camera);
void			hook_resize(int32_t width, int32_t height, void *gui_void);
void			init_gui_exit(t_gui *gui);
void			init_scene_exit(t_scene *scene);
void			calculate_camera(mlx_image_t *img, t_camera *camera);
void			debug_vec3(const char *msg, const t_vec3 *v);
void			debug_ray(const char *msg, const t_ray *ray);
void			debug_decimal(const char *msg, double d);
void			debug_material(const t_material *material);
void			debug_sphere(const t_sphere *sph);
void			render(void);
void			loop_rays(mlx_image_t *img, t_camera *camera);
void			sample_rays(uint32_t x, uint32_t y, mlx_image_t *img,
					t_camera *camera);
t_vec3			get_pix_pos_base(t_camera *camera, uint32_t x, uint32_t y);
t_ray			final_ray(const t_vec3 *base, t_camera *camera);
void			draw_stats(const char *string, t_gui *gui);
void			try_delete_stats(mlx_t *mlx, mlx_image_t **img_1,
					mlx_image_t **img_2);
void			update_stats(t_gui *gui, t_camera *camera);
int				get_time_ms(struct timeval *anchor);
long			get_time_us(struct timeval *anchor);
double			get_time_s(struct timeval *anchor);
void			reset_render_time(t_gui *gui);
void			pars_skip_space(char const **pp_pos);
bool			pars_atof_converted(char const **str_pos, double *num);
bool			pars_comma_skipped(char const **str_pos);
bool			pars_atoi_converted(const char **str_pos, int *result);
void			example_purple_spheres(t_dynamic_array *spheres);
void			example_first_spheres(t_dynamic_array *spheres);
void			example_fov_spheres(t_dynamic_array *spheres);
bool			pars_ambient_light(t_scene *scene, const char **line);
bool			pars_camera(t_scene *scene, const char **line);
bool			pars_light(t_scene *scene, const char **line);
bool			pars_sphere(t_scene *scene, const char **line);
bool			pars_plane(t_scene *scene, const char **line);
bool			pars_cylinder(t_scene *scene, const char **line);
bool			parse_line(t_scene *scene, const char **line_pos);
int				open_correct_file(int argc, char const *argv[],
					char const **filename);
void			pars_scene_exit(t_scene *scene, int argc, char const *argv[]);
bool			pars_coordinate_converted(const char **line_pos,
					t_vec3 *result);
bool			pars_coordinate_in_range_converted(const char **line_pos,
					t_vec3 *result, t_interval range);
bool			pars_double_in_range_converted(const char **line_pos,
					double *result, t_interval range);
bool			pars_int8_in_range_converted(const char **line_pos,
					uint8_t *result);
bool			pars_color_256_converted(const char **line_pos,
					t_color_256 *result_color);
bool			pars_color_vec3_converted(const char **line_pos,
					t_vec3 *result_color);
bool			pars_material_converted(const char **line_pos,
					t_material *result_material);
bool			is_hit_cylinder(const t_cylinder *cy, const t_ray *ray,
					const t_interval ray_boarder, t_norm_ray *hit);
t_cylinder		*nearest_hit_cylinder(const t_ray *ray, t_interval *ray_boarder,
					t_norm_ray *hit);
t_material		*nearest_hit_all(const t_ray *ray, t_interval *ray_boarder,
					t_norm_ray *hit);
bool			is_hit_plane(const t_plane *pl, const t_ray *ray,
					const t_interval ray_boarder, t_norm_ray *hit);
t_plane			*nearest_hit_plane(const t_ray *ray, t_interval *ray_boarder,
					t_norm_ray *hit);
bool			is_hit_sphere(const t_sphere *sph, const t_ray *ray,
					const t_interval ray_boarder, t_norm_ray *hit);
t_sphere		*nearest_hit_sphere(const t_ray *ray, t_interval *ray_boarder,
					t_norm_ray *hit);
t_vec3			get_random_on_hemisphere(const t_vec3 *hit_direction_normal);
void			test_hit_cylinder(void);
void			test_hit_cylinder_ext(void);
void			test_r3(void);
void			test_random(void);
void			test_dynamic_array(void);
void			test_hit_plane(void);
int				test_caller(int argc, char const *argv[]);
t_vec3			inverse_vec3(const t_vec3 a);
t_vec3			square_vec3(const t_vec3 a);
t_vec3			cross_vec3(const t_vec3 a, const t_vec3 b);
t_vec3			fabs_vec3(const t_vec3 *a);
t_vec3			normalize_vec3(const t_vec3 a);
void			normalize_vec3_p(t_vec3 *a);
t_vec3			get_pos_on_ray(const t_ray *ray, const double length);
t_vec3			reflect_vec3(const t_vec3 vector, const t_vec3 normal);
t_vec3			refract_vec3(const t_vec3 *unit_vector, const t_vec3 *normal,
					double etai_over_etat);
t_vec3			add_vec3(t_vec3 a, const t_vec3 b);
t_vec3			sub_vec3(t_vec3 a, const t_vec3 b);
t_vec3			mul_vec3(t_vec3 a, const t_vec3 b);
t_vec3			div_vec3(t_vec3 a, const t_vec3 b);
t_vec3			add_one_vec3(t_vec3 a, const double add);
t_vec3			sub_one_vec3(t_vec3 a, const double subtract);
t_vec3			mul_one_vec3(t_vec3 a, const double multiply);
t_vec3			div_one_vec3(t_vec3 a, const double divide);
void			add_vec3_p(t_vec3 *a, const t_vec3 b);
void			sub_vec3_p(t_vec3 *a, const t_vec3 b);
void			mul_vec3_p(t_vec3 *a, const t_vec3 b);
void			div_vec3_p(t_vec3 *a, const t_vec3 b);
void			add_one_vec3_p(t_vec3 *a, const double add);
void			sub_one_vec3_p(t_vec3 *a, const double subtract);
void			mul_one_vec3_p(t_vec3 *a, const double multiply);
void			div_one_vec3_p(t_vec3 *a, const double divide);
double			clamp(double value, t_interval interval);
void			clamp_p(double *value, t_interval interval);
t_vec3			clamp_vec3(t_vec3 value, t_interval interval);
void			clamp_vec3_p(t_vec3 *value, t_interval interval);
double			combine_vec3(const t_vec3 a);
double			dot_vec3(const t_vec3 a, const t_vec3 b);
double			length_squared_vec3(const t_vec3 a);
double			length_vec3(const t_vec3 a);
bool			is_bigger_vec3(const t_vec3 val, const t_vec3 against);
bool			is_interval_in_vec3(const t_vec3 value, const t_vec3 min,
					const t_vec3 max);
bool			is_near_zero(const double value);
bool			is_near_zero_vec3(const t_vec3 a);
double			degrees_to_radians(const double degrees);
double			linear_to_gamma(const double linear_color_part);
void			color_256_to_vec3(t_color_256 *in, t_vec3 *out);
bool			is_interval_in(const t_interval interval, const double value);
// end
#endif