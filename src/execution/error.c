/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 12:08:52 by rgohrig           #+#    #+#             */
/*   Updated: 2026/01/27 12:16:32 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "mini_rt.h"

void	program_exit(int exit_code)
{
	// free all
	exit(exit_code);
}

void	perror_exit(const char *msg, int exit_code)
{
	perror(msg);
	program_exit(exit_code);
}

void	msg_exit(const char *msg)
{
	ft_putstr_fd(msg, 2);
	program_exit(EXIT_FAILURE);
}

