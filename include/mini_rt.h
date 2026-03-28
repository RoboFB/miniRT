/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_rt.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ileon <ileon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 14:31:06 by rgohrig           #+#    #+#             */
/*   Updated: 2026/03/28 12:15:33 by ileon            ###   ########.fr       */
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

# ifndef M_PI
#  define M_PI		3.14159265358979323846
# endif

# ifndef BIG_DOUBLE
#  define BIG_DOUBLE	1e300
# endif

# define SMALL_DOUBLE	0.0001

extern const t_color_256	g_black;
extern const t_color_256	g_white;

typedef enum e_rt_defaults
{
	BPP = 4,
	WIDTH_DEFAULT = 800,
	HEIGHT_DEFAULT = 600,
	DEBUG_RT = 1,
}	t_rt_defaults;

#endif
