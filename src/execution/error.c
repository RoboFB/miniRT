/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 12:08:52 by rgohrig           #+#    #+#             */
/*   Updated: 2026/02/16 15:26:01 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "mini_rt.h"

void	program_exit(int exit_code)
{
	free_data();
	exit(exit_code);
}

void	perror_exit(const char *msg)
{
	perror(msg);
	program_exit(EXIT_FAILURE);
}

void	msg_exit(const char *msg)
{
	ft_putendl_fd(msg, 2);
	program_exit(EXIT_FAILURE);
}

void	msg_2_exit(const char *msg, const char *msg2)
{
	ft_putstr_fd(msg, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(msg2, 2);
	program_exit(EXIT_FAILURE);
}

void perror_mlx_exit(const char *msg)
{
	ft_putstr_fd(msg, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(mlx_strerror(mlx_get_errno()), 2);
	program_exit(EXIT_FAILURE);
}
