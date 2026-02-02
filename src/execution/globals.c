/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   globals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 18:51:34 by rgohrig           #+#    #+#             */
/*   Updated: 2026/01/27 18:51:41 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "mini_rt.h"

t_data	*get_data(void)
{
	static t_data	gui;

	return (&gui);
}

t_gui	*get_gui(void)
{
	return (&get_data()->gui);
}