/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 12:08:52 by rgohrig           #+#    #+#             */
/*   Updated: 2026/03/28 09:00:00 by ileon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

/* Frees all resources and exits with the given exit code. */
void	program_exit(int exit_code)
{
	free_data();
	exit(exit_code);
}

/* Prints a system error message (perror) and exits. */
void	perror_exit(const char *msg)
{
	perror(msg);
	program_exit(EXIT_FAILURE);
}

/* Prints a custom error message to stderr and exits. */
void	msg_exit(const char *msg)
{
	ft_putendl_fd(msg, 2);
	program_exit(EXIT_FAILURE);
}

/* Prints two combined error messages to stderr and exits. */
void	msg_2_exit(const char *msg, const char *msg2)
{
	ft_putstr_fd(msg, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(msg2, 2);
	program_exit(EXIT_FAILURE);
}

/* Prints an MLX error message and exits. */
void	perror_mlx_exit(const char *msg)
{
	ft_putstr_fd(msg, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(mlx_strerror(mlx_get_errno()), 2);
	program_exit(EXIT_FAILURE);
}
