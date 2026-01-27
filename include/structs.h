/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 14:31:06 by rgohrig           #+#    #+#             */
/*   Updated: 2026/01/27 20:05:40 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STURCTS_H
# define STURCTS_H

# include "MLX42.h"

# define MAX_CIR_QUEUE_SIZE 1000000


typedef struct s_gui
{
	mlx_t			*mlx;
	mlx_image_t		*img;
	mlx_image_t		*buffer_img;
}				t_gui;


typedef struct s_vec3
{
	double		x;
	double		y;
	double		z;
}				t_vec3;

typedef struct s_ray
{
	t_vec3		origin;
	t_vec3		direction;
}				t_ray;

typedef struct s_pixel
{
	uint32_t	x;
	uint32_t	y;
}				t_pixel;



typedef union
{
	uint8_t		bytes[4];
	uint32_t	value;
	struct {
		uint8_t			a;
		uint8_t			b;
		uint8_t			g;
		uint8_t			r;
	};
}			t_color_256;

// 0 to 1.0
typedef struct s_color_d
{
	double		r;
	double		g;
	double		b;
}				t_color_d;



typedef struct s_ambient_light
{
	double		ratio; // between 0.0 and 1.0
	t_color_256	color; // R G B 0-255 no alpha
}				t_ambient_light;

typedef struct s_camera
{
	t_vec3		position;
	t_vec3		orientation; // normalized vector (-1 to 1)
	double		fov; 		// between 0 and 180 for horizontal FOV
}				t_camera;

typedef struct s_light
{
	t_vec3		position;
	double		ratio; // between 0.0 and 1.0
	t_color_256		color; // R G B 0-255 no alpha for bonus
}				t_light;

typedef struct s_sphere
{
	t_vec3		position;
	double		diameter;
	t_color_256		color; // R G B 0-255 no alpha for bonus
}				t_sphere;

typedef struct s_plane
{
	t_vec3		position;
	t_vec3		orientation;
	t_color_256		color; // R G B 0-255 no alpha for bonus
}				t_plane;

typedef struct s_cylinder
{
	t_vec3		position;
	t_vec3		orientation;
	double		diameter;
	double		height;
	t_color_256		color; // R G B 0-255 no alpha for bonus
}				t_cylinder;


typedef struct s_cir_queue
{
	t_pixel			data[MAX_CIR_QUEUE_SIZE];
	int32_t			front;
	uint32_t		size;
	uint32_t		capacity;
}		t_cir_queue;


typedef struct s_data
{
	// mlx destroy at the end
	t_gui			gui;

	t_camera		camera;
	t_light			light;
	t_ambient_light	ambient_light;


	// // mallocs free at the end
	// t_cir_queue		*cir_qu;
	// t_cir_queue		*q_tmp_black;

	// // options/user input
	// t_fractal_typ	fractal_typ;
	// t_vec3			fractal_start;

	// math part
	// uint32_t		max_iterations;
	// t_vec3			center_view;
	// double			width_view;
	// double			height_view;

	// info massage
	// uint32_t		pixels_per_frame;

	// color shift
	// uint32_t		color_offset;

}		t_data;


#endif
