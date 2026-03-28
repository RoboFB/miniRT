/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 14:31:06 by rgohrig           #+#    #+#             */
/*   Updated: 2026/03/06 15:02:01 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

// # include "MLX42.h"

typedef struct s_vec3
{
	double			x;
	double			y;
	double			z;
}					t_vec3;

typedef struct s_ray
{
	t_vec3			origin;
	t_vec3			direction;
}					t_ray;

typedef struct s_interval
{
	double			min;
	double			max;
}					t_interval;

typedef struct s_pixel
{
	uint32_t		x;
	uint32_t		y;
}					t_pixel;

// use img_draw_256 to draw this
// raw: 0 to 255 (rgba) in memory as rgba dont use mlx_put_pixel
typedef union u_color_256
{
	uint8_t			bytes[4];
	uint32_t		value;
	struct
	{
		uint8_t		r;
		uint8_t		g;
		uint8_t		b;
		uint8_t		a;
	};
}					t_color_256;

typedef struct s_norm_ray
{
	t_ray			r;
	double			length;// factor for ray length
}					t_norm_ray;


typedef struct s_scene t_scene; // forward declaration for parser function pointer
typedef struct s_parser_entry
{
	char			name[3];
	bool			(*func)(t_scene *scene, const char **line);
}					t_parser_entry;




typedef struct s_ambient_light
{
	double			ratio; // between 0.0 and 1.0
	t_vec3			color; // R G B 0-255 no alpha
}					t_ambient_light;

// there is only one camera in the scene
typedef struct s_camera
{
	t_norm_ray		ray; // r.origin random point, r.direction normalized vector (-1 to 1) length = focal_length; // 1.0
	double			fov; 		 // between 0 and 180 for horizontal FOV
	t_vec3 			delta_u;
	t_vec3			delta_v;
	t_vec3			corner_upper_left;
	int32_t			max_deep_rays;
	uint32_t		anti_aliasing_samples;
}					t_camera;


typedef struct s_light
{
	t_vec3			position;
	double			ratio; // between 0.0 and 1.0
	t_vec3			color; // R G B 0-255 no alpha for bonus
}					t_light;

typedef enum e_material_type
{
	MATERIAL_NONE			= 0b00000000,
	MATERIAL_PHONG			= 0b00000001, // default phone light model
	MATERIAL_LAMBERTIAN		= 0b00000010, //like normal obj with path dracing
	MATERIAL_REFLECTION		= 0b00000100, //like metal
	MATERIAL_DIELECTRIC		= 0b00001000, //like glass
	MATERIAL_ALL			= 0b11111111,
}					t_material_type;

typedef struct s_material
{
	t_material_type	type;
	t_vec3			color; // RGB 0.0 to 1.0
	double			fuzz; // between 0.0 and 1.0 for metal
	double			refraction_index; // for dielectric

}					t_material;

typedef struct s_sphere
{
	t_vec3			center;
	double			radius; // needs to be positive
	t_material		material;
}					t_sphere;

typedef struct s_plane
{
	t_ray			plane;
	t_material		material;
}					t_plane;

typedef struct s_cylinder
{
	t_norm_ray		cylinder;
	double			radius;  // needs to be positive
	t_material		material;
}					t_cylinder;

// Precomputed quadratic coefficients for ray-cylinder tube intersection.
// Separates the heavy math from the root-finding logic.
typedef struct s_cy_data
{
	double			a;
	double			half_b;
	double			c;
	double			dv;
	double			wv;
}					t_cy_data;


typedef enum e_stats_type
{
	STATS_RAYS_SEC,
	STATS_NONE,

	STATS_MAX,

}					t_stats_type;

typedef struct s_statistics
{
	t_stats_type	type;
	struct timeval	time_before_render;
	int				rays_rendered;
	mlx_image_t		*str_img;
	mlx_image_t		*background_img;

}					t_statistics;

// stores gui and scene pointer
typedef struct s_gui
{
	mlx_t			*mlx;
	mlx_image_t		*img;
	mlx_image_t		*buffer_img;// the image on the screen to modify the normal img.

	t_statistics	statistics;

}					t_gui;

// scene related (objects, setting, etc)
typedef struct s_scene
{
	t_camera		*camera;
	t_ambient_light	*ambient_light;
	
	t_dynamic_array	lights;
	t_dynamic_array	spheres;
	t_dynamic_array	planes;
	t_dynamic_array	cylinders;
}					t_scene;

typedef struct s_data
{
	// mlx/window related
	t_gui			gui;

	t_scene			scene;
}		t_data;


#endif
