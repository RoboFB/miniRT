/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 11:56:59 by rgohrig           #+#    #+#             */
/*   Updated: 2026/02/17 16:18:40 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "mini_rt.h"



// R; true = success, error = false
bool pars_coordinate_converted(const char **line_pos, t_vec3 *result)
{
	if (!pars_atof_converted(line_pos, &result->x))
		return (false);
	if (!pars_comma_skipped(line_pos))
		return (false);
	if (!pars_atof_converted(line_pos, &result->y))
		return (false);
	if (!pars_comma_skipped(line_pos))
		return (false);
	if (!pars_atof_converted(line_pos, &result->z))
		return (false);
	return (true);
}

// R; true = success, error = false
bool pars_coordinate_interval_converted(const char **line_pos, t_vec3 *result, t_interval range)
{
	if (!pars_double_in_range_converted(line_pos, &result->x, range))
		return (false);
	if (!pars_comma_skipped(line_pos))
		return (false);
	if (!pars_double_in_range_converted(line_pos, &result->y, range))
		return (false);
	if (!pars_comma_skipped(line_pos))
		return (false);
	if (!pars_double_in_range_converted(line_pos, &result->z, range))
		return (false);
	return (true);
}

// R; true = success, error = false
bool pars_double_in_range_converted(const char **line_pos, double *result, t_interval range)
{
	if (!pars_atof_converted(line_pos, result))
		return (false);
	
	if (!is_interval_in(range, *result))
		return (false);
	
	return (true);
}

// R; true = success, error = false
bool pars_int8_in_range_converted(const char **line_pos, uint8_t *result)
{
	int tmp;
	if (!pars_atoi_converted(line_pos, &tmp))
		return (false);
	
	if (tmp < 0 || tmp > 255)
		return (false);
	*result = tmp;
	return (true);
}


// R; true = success, error = false
bool pars_color_256_converted(const char **line_pos, t_color_256 *result_color)
{
	printf("_str:_%s\n", *line_pos);
	if (!pars_int8_in_range_converted(line_pos, &result_color->r))
	return (false);
	printf("_str:_%s\n", *line_pos);
	if (!pars_comma_skipped(line_pos))
	return (false);
	printf("_str:_%s\n", *line_pos);
	if (!pars_int8_in_range_converted(line_pos, &result_color->g))
		return (false);
	if (!pars_comma_skipped(line_pos))
		return (false);
	if (!pars_int8_in_range_converted(line_pos, &result_color->b))
		return (false);
	result_color->a = 255; // default alpha to fully opaque
	return (true);
}

// R; true = success, error = false
bool pars_color_vec3_converted(const char **line_pos, t_vec3 *result_color)
{
	t_color_256 temp_color;

	if (!pars_color_256_converted(line_pos, &temp_color))
		return (false);
	color_256_to_vec3(&temp_color, result_color);
	return (true);
}

// returns (true) on success/saved line, (false) on error/parsed line
bool parse_line(t_scene *scene, char *line)
{
	static const t_parser_entry parser_entries[6] = {
		{"A", &pars_ambient_light},
		{"C", &pars_camera},
		{"L", &pars_light},
		{"sp", &pars_sphere},
		{"pl", &pars_plane},
		{"cy", &pars_cylinder}
	};

	int pos = 0;
	if (line == NULL)
		return (false);
	if (line[0] == '\n' || line[0] == '#')
	{
		return (false);
	}
	while (pos < 6)
	{
		if (ft_strncmp(line, parser_entries[pos].name, ft_strlen(parser_entries[pos].name)) == 0)
		{
			line += ft_strlen(parser_entries[pos].name) + 1;
			return (parser_entries[pos].func(scene, line));
		}
		pos++;
	}
	return (false);
}

// R: 0 = success, else error
int init_scene(t_scene *scene, int argc, char const *argv[])
{
	int file_fd;

	file_fd = -1;
	if (argc == 1)
	{
		file_fd = STDIN_FILENO;
		ft_printf("Reading scene from standard input. Press Ctrl+D to finish.\n");
	}
	else if (argc == 2)
	{
		char *filename = (char *)argv[1];
		size_t len = ft_strlen(filename);
		if (len < 3 || ft_strncmp(filename + len - 3, ".rt", 4) != 0)
			msg_2_exit(filename, "Invalid file name. needs to end with .rt");

		file_fd = open(filename, O_RDONLY);
		if (file_fd < 0)
			perror_exit(filename);
	}
	else
	{
		msg_exit("Too many arguments, expected only the scene file");
	}

	scene->spheres = dynamic_array_init(sizeof(t_sphere));
	scene->camera = ft_calloc(1, sizeof(t_camera));// todo: implement null check
	init_camera(get_gui()->img, scene->camera);

	// call all parsing line convrting fuctions dont exit becose of the open file!
	while (true)
	{
		char *line = get_next_line(file_fd);
		if (line == NULL)
			break;
		(void)parse_line(scene, line);
		free(line);
	}
	close(file_fd);



	// scene->all_rays = ft_calloc(get_gui()->img->width * get_gui()->img->height, sizeof(t_ray));// todo: implement null check


	// init_sphere(scene);
	// test_fov(scene);
	// purple_spheres(scene);

	debug_sphere(scene->spheres.first);
	return (0);
}

void	purple_spheres(t_scene *scene)
{
	dynamic_array_add_back(&scene->spheres, &(t_sphere){ // left
		.center = (t_vec3){-0.5, 0.0, -1.0},
		.radius = 0.5,
		.material = (t_material){
			.type = MATERIAL_LAMBERTIAN,
			.color = (t_vec3){0.1, 0.000001, 0.1},
		},
	});
	dynamic_array_add_back(&scene->spheres, &(t_sphere){ // ground
		.center = (t_vec3){0.0, -100.5, -1.0},
		.radius = 100.0,
		.material = (t_material){
			.type = MATERIAL_METAL,
			.color = (t_vec3){0.7, 0.7, 0.7},
			.fuzz = 0.01,
		},
	});
	dynamic_array_add_back(&scene->spheres, &(t_sphere){ // in 0.4r 1.5
		.center = (t_vec3){0.5, 0.2, -1.0},
		.radius = 0.4,
		.material = (t_material){
			.type = MATERIAL_DIELECTRIC,
			.color = (t_vec3){0.7, 0.7, 0.7},
			.refraction_index = 1.0/1.5,
		},
	});
	dynamic_array_add_back(&scene->spheres, &(t_sphere){ // out 0.5r 1.0
		.center = (t_vec3){0.5, 0.2, -1.0},
		.radius = 0.5,
		.material = (t_material){
			.type = MATERIAL_DIELECTRIC,
			.color = (t_vec3){0.7, 0.7, 0.7},
			.refraction_index = 1.0,
		},
	});
}

void init_sphere(t_scene *scene)
{
	dynamic_array_add_back(&scene->spheres, &(t_sphere){
		.center = (t_vec3){0.0, -100.5, -1.0},
		.radius = 100.0,
		.material = (t_material){
			.type = MATERIAL_LAMBERTIAN,
			.color = (t_vec3){0.8, 0.8, 0.0},
		},
	});
	dynamic_array_add_back(&scene->spheres, &(t_sphere){
		.center = (t_vec3){0.0, 0.0, -1.2},
		.radius = 0.5,
		.material = (t_material){
			.type = MATERIAL_LAMBERTIAN,
			.color = (t_vec3){0.1, 0.2, 0.5},
		},
	});
	dynamic_array_add_back(&scene->spheres, &(t_sphere){
		.center = (t_vec3){-1.0, 0.0, -1.0},
		.radius = 0.5,
		.material = (t_material){
			.type = MATERIAL_DIELECTRIC,
			.refraction_index = 1.50,
		},
	});
	dynamic_array_add_back(&scene->spheres, &(t_sphere){
		.center = (t_vec3){-1.0, 0.0, -1.0},
		.radius = 0.4,
		.material = (t_material){
			.type = MATERIAL_DIELECTRIC,
			.refraction_index = 1.0 / 1.50,
		},
	});
	dynamic_array_add_back(&scene->spheres, &(t_sphere){
		.center = (t_vec3){1.0, 0.0, -1.0},
		.radius = 0.5,
		.material = (t_material){
			.type = MATERIAL_METAL,
			.color = (t_vec3){0.8, 0.6, 0.2},
			.fuzz = 1,
		},
	});
}


void test_fov(t_scene *scene)
{
	double radius = cos(M_PI/4.0);

	dynamic_array_add_back(&scene->spheres, &(t_sphere){
		.center = (t_vec3){-radius, 0.0, -1.0},
		.radius = radius,
		.material = (t_material){
			.type = MATERIAL_LAMBERTIAN,
			.color = (t_vec3){0.0, 0.0, 1.0},
		},
	});
	dynamic_array_add_back(&scene->spheres, &(t_sphere){
		.center = (t_vec3){radius, 0.0, -1.0},
		.radius = radius,
		.material = (t_material){
			.type = MATERIAL_LAMBERTIAN,
			.color = (t_vec3){1.0, 0.0, 0.0},
		},
	});
}


t_camera	*init_camera(mlx_image_t *img, t_camera *camera)
{

	camera->ray.r.origin = (t_vec3){0, 0, 0.0};
	camera->ray.r.direction = (t_vec3){0.0, 0.0,-1.0};
	camera->ray.length = 1.0; // focal length
	camera->fov = 90.0;
	camera->max_deep_rays = 16;
	camera->anti_aliasing_samples = 16; // no *2 in main hock

	
	double scale = tan(degrees_to_radians(camera->fov) * 0.5);
	
	double viewport_height = 2.0 * scale * camera->ray.length;
	double imageAspectRatio = (double)img->width / (double)img->height;
	double viewport_width = viewport_height * imageAspectRatio;
	

	// Calculate the u,v,w unit basis vectors for the camera coordinate frame.
	t_vec3 vup = (t_vec3){0.0, 1.0, 0.0}; // relative up for changeing angels later if needed
	t_vec3 w = normalize_vec3(camera->ray.r.direction); //z
	t_vec3 u = normalize_vec3(cross_vec3(vup, w)); // x
	t_vec3 v = cross_vec3(w, u); //y

	t_vec3 viewport_u = mul_one_vec3(u, viewport_width);
	t_vec3 viewport_v = mul_one_vec3(v, viewport_height);

	camera->delta_u = div_one_vec3(viewport_u, (double)(img->width));
	camera->delta_v = div_one_vec3(viewport_v, (double)(img->height));
	
	// Start at focal point (in front of camera), then move to upper-left corner
	camera->corner_upper_left = add_vec3(camera->ray.r.origin, mul_one_vec3(w, camera->ray.length));
	// debug_vec3("corner1", &camera->corner_upper_left);
	
	add_vec3_p(&camera->corner_upper_left, mul_one_vec3(viewport_u, 0.5));
	// debug_vec3("corner2", &camera->corner_upper_left);
	
	add_vec3_p(&camera->corner_upper_left, mul_one_vec3(viewport_v, 0.5));
	// debug_vec3("corner3", &camera->corner_upper_left);
	
	
	// debug_vec3("w", &w);
	// debug_vec3("u", &u);
	// debug_vec3("v", &v);
	
	return (camera);
}

