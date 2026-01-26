/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 16:53:04 by rgohrig           #+#    #+#             */
/*   Updated: 2025/03/31 14:24:32 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_get_len(int n);
static void		ft_insert_revers(char *dst, int n, int len);

// F: Malloc R: str or NULL
char	*ft_itoa(int n)
{
	int		len;
	char	*str;

	len = ft_get_len(n);
	str = ft_calloc(len + 1, sizeof(char));
	if (!str)
		return (NULL);
	ft_insert_revers(str, n, len);
	return (str);
}

static
int	ft_get_len(int n)
{
	int	len;

	len = 0;
	if (n == -2147483648)
	{
		n = n / 10;
		len++;
	}
	if (n < 0)
	{
		len++;
		n *= -1;
	}
	if (0 <= n && n <= 9)
		len++;
	else
	{
		len += ft_get_len(n / 10);
		len ++;
		return (len);
	}
	return (len);
}

static
void	ft_insert_revers(char *dst, int n, int len)
{
	int	idx;

	idx = len;
	if (n == -2147483648)
	{
		ft_strlcpy(dst, "-2147483648", 12);
		return ;
	}
	if (n < 0)
	{
		dst[0] = '-';
		n *= -1;
	}
	dst[idx--] = '\0';
	if (!n)
		dst[idx] = '0';
	while (n)
	{
		dst[idx--] = '0' + n % 10;
		n /= 10;
	}
	return ;
}
