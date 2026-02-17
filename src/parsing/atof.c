/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atof.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 15:28:53 by rgohrig           #+#    #+#             */
/*   Updated: 2026/02/17 15:29:27 by rgohrig          ###   ########.fr       */
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
// Input: str | Output: num | R: true(OK) false(Error)
bool	pars_atof_converted(char const **str_pos, double *num)
{
	double		negative;

	*num = 0.0;
	h_skip_space(str_pos);
	negative = h_get_negative(str_pos);
	if (h_get_base_num(str_pos, num) < 0)
		return (false);
	if (*num == 0.0)
		return (true);
	*num *= pow(10.0, h_get_exp(str_pos));
	if (!isfinite(*num) || *num == 0.0)
		return (false);
	*num *= negative;
	return (true);
}

// convert and skip comma
bool	pars_comma_skipped(char const **str_pos)
{
	if (**str_pos == ',')
	{
		(*str_pos)++;
		return (true);
	}
	else
	{
		return (false);
	}
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

// R: true(OK) false(Error)
bool	pars_atoi_converted(const char **str_pos, int *result)
{
	long int	num;
	int			negative;

	num = 0;
	negative = 1;
	if (!str_pos || !*str_pos || !**str_pos)
		return (false);
	h_skip_space(str_pos);
	if (**str_pos == '-')
	{
		negative = -1;
		(*str_pos)++;
	}
	if (!ft_isdigit(**str_pos))
		return (false);
	while (ft_isdigit(**str_pos))
	{
		num = num * 10 + (**str_pos - '0') * negative;
		if (num < INT_MIN || num > INT_MAX)
			return (false);
		(*str_pos)++;
	}
	*result = (int)num;
	return (true);
}
