/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 10:20:57 by rgohrig           #+#    #+#             */
/*   Updated: 2025/06/25 11:28:06 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdarg.h>
# include <stdint.h>

// printf functions

int			ft_printf(const char *main_str, ...);
int			ft_prf_putchar(char one_char);
int			ft_prf_str(char *str);
int			ft_prf_hex(unsigned int nbr, char letter_start, int written_chars);
int			ft_prf_pointer(uintptr_t nbr, char letter_start, int written_chars);
int			ft_prf_uint(unsigned int nbr, int written_chars);
int			ft_prf_int(int nbr, int written_chars);

#endif
