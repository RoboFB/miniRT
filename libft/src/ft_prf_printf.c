/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 15:39:08 by rgohrig           #+#    #+#             */
/*   Updated: 2025/04/04 12:56:06 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static
int	ft_conversion(const char *conversion, va_list arg)
{
	int		result;

	result = -1;
	if (*conversion == 'c')
		result = ft_prf_putchar(va_arg(arg, int));
	else if (*conversion == 's')
		result = ft_prf_str(va_arg(arg, char *));
	else if (*conversion == 'p')
		result = ft_prf_pointer(va_arg(arg, uintptr_t), 'a', 0);
	else if (*conversion == 'd' || *conversion == 'i')
		result = ft_prf_int(va_arg(arg, int), 0);
	else if (*conversion == 'u')
		result = ft_prf_uint(va_arg(arg, int), 0);
	else if (*conversion == 'x')
		result = ft_prf_hex(va_arg(arg, unsigned int), 'a', 0);
	else if (*conversion == 'X')
		result = ft_prf_hex(va_arg(arg, unsigned int), 'A', 0);
	else if (*conversion == '%')
		result = ft_prf_putchar('%');
	return (result);
}

int	ft_printf(const char *main_str, ...)
{
	va_list	arg;
	int		written_chars;
	int		result;

	va_start(arg, main_str);
	written_chars = 0;
	result = 0;
	while (*main_str)
	{
		if (*main_str == '%')
		{
			result = ft_conversion (main_str + 1, arg);
			if (result < 0)
				return (result);
			written_chars += result;
			main_str += 2;
			continue ;
		}
		if (ft_prf_putchar(*main_str) < 0)
			return (-1);
		written_chars++;
		main_str++;
	}
	va_end(arg);
	return (written_chars);
}
