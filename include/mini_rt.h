/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_rt.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 14:31:06 by rgohrig           #+#    #+#             */
/*   Updated: 2026/03/02 16:49:37 by rgohrig          ###   ########.fr       */
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

# include "dynamic_array.h"
# include "structs.h"
# include "function_definitions.h"

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


#endif
