/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 16:28:27 by rgohrig           #+#    #+#             */
/*   Updated: 2025/03/31 14:31:48 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_list
	*ft_lstfirst(t_list *lst, void *(*f)(void *), void (*del)(void *));

// F: malloc, free R: duplicated/mapped *lst or NULL
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list		*new_node;
	t_list		*start_new_lst;
	void		*new_content;

	if (!lst || !f || !del)
		return (NULL);
	new_node = ft_lstfirst(lst, f, del);
	if (!new_node)
		return (NULL);
	start_new_lst = new_node;
	lst = lst->next;
	while (lst)
	{
		new_content = f(lst->content);
		new_node->next = ft_lstnew(new_content);
		if (!new_node->next)
		{
			del(new_content);
			ft_lstclear(&start_new_lst, del);
			return (NULL);
		}
		new_node = new_node->next;
		lst = lst->next;
	}
	return (start_new_lst);
}

// F: malloc R: new_node or NULL
static t_list
	*ft_lstfirst(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list		*new_node;
	void		*new_content;

	if (!lst || !f || !del)
		return (NULL);
	new_content = f(lst->content);
	new_node = ft_lstnew(new_content);
	if (!new_node)
	{
		del(new_content);
		return (NULL);
	}
	return (new_node);
}
