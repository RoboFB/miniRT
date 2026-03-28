/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   globals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ileon <ileon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 18:51:34 by rgohrig           #+#    #+#             */
/*   Updated: 2026/03/28 12:14:14 by ileon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

const t_color_256	g_black = {.a = 255};
const t_color_256	g_white = {.r = 255, .g = 255, .b = 255, .a = 255};

/* Returns a pointer to the global t_data singleton. */
t_data	*get_data(void)
{
	static t_data	data;

	return (&data);
}

/* Returns a pointer to the global t_gui singleton. */
t_gui	*get_gui(void)
{
	return (&get_data()->gui);
}

/* Returns a pointer to the global t_scene singleton. */
t_scene	*get_scene(void)
{
	return (&get_data()->scene);
}
