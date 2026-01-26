/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 15:19:39 by rgohrig           #+#    #+#             */
/*   Updated: 2025/03/31 14:30:23 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// F: Malloc R: *new_node or NULL
t_list	*ft_lstnew(void *content)
{
	t_list		*new_node;

	new_node = ft_calloc(1, sizeof(t_list));
	if (!new_node)
		return (NULL);
	new_node->content = content;
	new_node->next = 0;
	return (new_node);
}
