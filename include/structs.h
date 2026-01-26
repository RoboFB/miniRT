/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 14:31:06 by rgohrig           #+#    #+#             */
/*   Updated: 2026/01/26 17:34:07 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STURCTS_H
# define STURCTS_H

# include "MLX42.h"

typedef struct s_data
{
	// mlx destroy at the end
	mlx_t			*mlx;
	mlx_image_t		*img;
	mlx_image_t		*screen_img;

	// // mallocs free at the end
	// t_cir_queue		*cir_qu;
	// t_cir_queue		*q_tmp_black;

	// // options/user input
	// t_fractal_typ	fractal_typ;
	// t_cplx			fractal_start;

	// math part
	// uint32_t		max_iterations;
	// t_cplx			center_view;
	// double			width_view;
	// double			height_view;

	// info massage
	// uint32_t		pixels_per_frame;

	// color shift
	// uint32_t		color_offset;

}		t_data;


typedef struct s_position
{
	double		x;
	double		y;
	double		z;
}				t_position;


typedef struct s_pixel
{
	uint32_t	x;
	uint32_t	y;
}				t_pixel;



typedef struct s_color
{
	uint8_t		r;
	uint8_t		g;
	uint8_t		b;
}			t_color;


typedef struct s_ambient_light
{
	double		ratio; // between 0.0 and 1.0
	t_color		color; // R G B 0-255 no alpha
}				t_ambient_light;

typedef struct s_camera
{
	t_position	position;
	t_position	orientation; // normalized vector (-1 to 1)
	double		fov; 		// between 0 and 180 for horizontal FOV
}				t_camera;

typedef struct s_light
{
	t_position	position;
	double		ratio; // between 0.0 and 1.0
	t_color		color; // R G B 0-255 no alpha for bonus
}				t_light;

typedef struct s_sphere
{
	t_position	position;
	double		diameter;
	t_color		color; // R G B 0-255 no alpha for bonus
}				t_light;

typedef struct s_plane
{
	t_position	position;
	t_position	orientation;
	t_color		color; // R G B 0-255 no alpha for bonus
}				t_light;

typedef struct s_cylinder
{
	t_position	position;
	t_position	orientation;
	double		diameter;
	double		height;
	t_color		color; // R G B 0-255 no alpha for bonus
}				t_light;


// typedef struct s_cir_queue
// {
// 	t_pix			data[MAX_CIR_QUEUE_SIZE];
// 	int32_t			front;
// 	uint32_t		size;
// 	uint32_t		capacity;
// }		t_cir_queue;



#endif
