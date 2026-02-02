/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atof.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 15:28:53 by rgohrig           #+#    #+#             */
/*   Updated: 2026/01/26 17:56:22 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

static void	h_skip_space(char const **pp_pos)
{
	char const	*position;

	position = *pp_pos;
	while (*position == ' ' || *position == '\f' || *position == '\n'
		|| *position == '\r' || *position == '\t' || *position == '\v')
		position++;
	*pp_pos = position;
	return ;
}

static double	h_get_negative(char const **pp_pos)
{
	char const	*position;
	double		out;

	position = *pp_pos;
	out = 1.0;
	if (*position == '+')
		position++;
	else if (*position == '-')
	{
		out = -1.0;
		position++;
	}
	*pp_pos = position;
	return (out);
}

static int	h_get_base_num(char const **pp_pos, double *num)
{
	char const	*position;
	char const	*start;
	double		decimal_place;

	position = *pp_pos;
	start = *pp_pos;
	decimal_place = 0.1;
	while (*position >= '0' && *position <= '9')
		*num = *num * 10 + (*position++ - '0');
	if (*position == '.')
	{
		position++;
		while (*position >= '0' && *position <= '9')
		{
			*num = *num + ((*position - '0') * decimal_place);
			decimal_place *= 0.1;
			position++;
		}
	}
	*pp_pos = position;
	if (position == start)
		return (-1);
	return (0);
}

static double	h_get_exp(char const **pp_pos)
{
	char const	*position;
	double		exp;
	double		negative;

	position = *pp_pos;
	exp = 0.0;
	negative = 1.0;
	if (*position == 'e' || *position == 'E')
	{
		position++;
		if (*position == '+')
			position++;
		else if (*position == '-')
		{
			negative = -1.0;
			position++;
		}
		while (*position >= '0' && *position <= '9')
		{
			exp = exp * 10.0 + (*position - '0');
			position++;
		}
	}
	*pp_pos = position;
	return (exp * negative);
}

// convert string to double, should be safe, but not completely strict at end
// Input: str | Output: num | R: 0(OK) -1(Error)
int	fr_atof(char const *str, double *num)
{
	double		negative;

	*num = 0.0;
	h_skip_space(&str);
	negative = h_get_negative(&str);
	if (h_get_base_num(&str, num) < 0)
		return (-1);
	if (*num == 0.0)
		return (0);
	*num *= pow(10.0, h_get_exp(&str));
	if (!isfinite(*num) || *num == 0.0)
		return (-1);
	*num *= negative;
	return (0);
}

/*
- 12345 . 4242 x10 - 33
-		Sign of mantissa   -/+
12345	Location of decimal point
4242	Mantissa
x10		Base
-		Sine of exponent
33		Exponent
*/
