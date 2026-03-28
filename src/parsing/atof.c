/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atof.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ileon <ileon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 15:28:53 by rgohrig           #+#    #+#             */
/*   Updated: 2026/03/28 12:12:17 by ileon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

/* Advances the string pointer past any leading whitespace. */
void	pars_skip_space(char const **pp_pos)
{
	char const	*position;

	position = *pp_pos;
	while (*position == ' ' || *position == '\f' || *position == '\n'
		|| *position == '\r' || *position == '\t' || *position == '\v')
		position++;
	*pp_pos = position;
}

/* Reads an optional leading minus sign; returns -1.0 or 1.0. */
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

/* Reads the integer and optional decimal part of a float into *num. */
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

/* Reads an optional exponent suffix (e.g. e-3) and returns the multiplier. */
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

/* Parses a float from the string, advancing the pointer; false on failure. */
bool	pars_atof_converted(char const **str_pos, double *num)
{
	double	negative;

	*num = 0.0;
	pars_skip_space(str_pos);
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
