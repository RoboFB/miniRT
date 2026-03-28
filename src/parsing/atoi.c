/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 15:28:53 by rgohrig           #+#    #+#             */
/*   Updated: 2026/03/28 09:00:00 by ileon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

/* Skips optional whitespace and a comma separator; false if no comma found. */
bool	pars_comma_skipped(char const **str_pos)
{
	if (**str_pos == ',')
	{
		(*str_pos)++;
		return (true);
	}
	return (false);
}

/* Parses a decimal integer from the string, advancing pointer; false on err. */
bool	pars_atoi_converted(const char **str_pos, int *result)
{
	long int	num;
	int			negative;

	num = 0;
	negative = 1;
	if (!str_pos || !*str_pos || !**str_pos)
		return (false);
	pars_skip_space(str_pos);
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
