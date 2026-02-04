/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 14:31:06 by rgohrig           #+#    #+#             */
/*   Updated: 2026/02/03 18:43:58 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "MLX42.h"

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
	struct {
		uint8_t		r;
		uint8_t		g;
		uint8_t		b;
		uint8_t		a;
	};
}			t_color_256;

// 0 to 1.0
typedef struct s_color_d
{
	double			r;
	double			g;
	double			b;
}					t_color_d;

typedef struct s_norm_ray
{
	t_ray			r;
	double			length;// factor for ray length
}					t_norm_ray;

typedef struct s_ambient_light
{
	double			ratio; // between 0.0 and 1.0
	t_color_256		color; // R G B 0-255 no alpha
}					t_ambient_light;

// there is only one camera in the scene
typedef struct s_camera
{
	t_vec3			position;
	t_vec3			orientation; // normalized vector (-1 to 1)
	double			fov; 		 // between 0 and 180 for horizontal FOV
	double			focal_length; // 1.0
	double 			delta_x;
	double			delta_y;
	t_vec3			corner_upper_left;
}					t_camera;

typedef struct s_light
{
	t_vec3			position;
	double			ratio; // between 0.0 and 1.0
	t_color_256		color; // R G B 0-255 no alpha for bonus
}				t_light;

typedef struct s_sphere
{
	t_vec3			center;
	double			radius; // needs to be positive
	t_color_256		color; // R G B 0-255 no alpha for bonus
}				t_sphere;

typedef struct s_plane
{
	t_vec3			position;
	t_vec3			orientation;
	t_color_256		color; // R G B 0-255 no alpha for bonus
}					t_plane;

typedef struct s_cylinder
{
	t_vec3			position;
	t_vec3			orientation;
	double			diameter;
	double			height;
	t_color_256		color; // R G B 0-255 no alpha for bonus
}					t_cylinder;





// stores gui and scene pointer
typedef struct s_gui
{
	mlx_t			*mlx;
	mlx_image_t		*img;
	mlx_image_t		*buffer_img;// the image on the screen to modify the normal img.
}					t_gui;

// scene related (objects, setting, etc)
typedef struct s_scene
{
	t_camera		*camera;
	t_light			*light;
	// t_ambient_light	*ambient_light;

	t_dynamic_array		spheres;
	// t_plane			*all_planes;
	// t_cylinder		*all_cylinders;

	t_ray			*all_rays; //basic array

}					t_scene;

typedef struct s_data
{
	// mlx/window related
	t_gui			gui;

	t_scene			scene;
}		t_data;


#endif
