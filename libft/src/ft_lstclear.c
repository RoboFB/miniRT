/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 16:28:18 by rgohrig           #+#    #+#             */
/*   Updated: 2025/03/28 15:10:19 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// F: free
void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	if (!lst || !del || !*lst)
		return ;
	if ((*lst)->next)
		ft_lstclear(&((*lst)->next), del);
	ft_lstdelone(*lst, del);
	*lst = NULL;
	return ;
}
