/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 16:53:16 by rgohrig           #+#    #+#             */
/*   Updated: 2025/03/31 14:28:19 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// F: write
void	ft_putnbr_fd(int n, int fd)
{
	if (n == -2147483648)
	{
		ft_putstr_fd("-2147483648", fd);
		return ;
	}
	if (n < 0)
	{
		n *= -1;
		ft_putchar_fd('-', fd);
	}
	if (0 <= n && n <= 9)
	{
		ft_putchar_fd('0' + n, fd);
		return ;
	}
	ft_putnbr_fd(n / 10, fd);
	ft_putchar_fd('0' + n % 10, fd);
	return ;
}
