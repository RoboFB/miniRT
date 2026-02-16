/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 16:56:34 by rgohrig           #+#    #+#             */
/*   Updated: 2025/04/23 14:46:32 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// R: void
void	add_node_to_end(t_str_list **lst, t_str_list *new)
{
	t_str_list		*end;

	if (!lst || !new)
		return ;
	end = *lst;
	if (!end)
	{
		*lst = new;
		return ;
	}
	while (end->next)
		end = end->next;
	end->next = new;
	return ;
}

// F: Malloc   R: (*new_node)OK (NULL)errorM
t_str_list	*make_node(char *str, size_t len)
{
	t_str_list		*new_node;
	size_t			idx;

	idx = 0;
	new_node = malloc(sizeof(t_str_list));
	if (!new_node)
		return (NULL);
	new_node->len = len;
	new_node->next = NULL;
	while (idx < len)
	{
		new_node->str[idx] = str[idx];
		idx++;
	}
	while (idx < BUFFER_SIZE)
	{
		new_node->str[idx] = '\0';
		idx++;
	}
	return (new_node);
}

// R: (len_all)OK (0)no lst
size_t	len_all_str(t_str_list *lst)
{
	size_t			len_all;

	len_all = 0;
	while (lst)
	{
		len_all += lst->len;
		lst = lst->next;
	}
	return (len_all);
}

// F: free   R: void
void	lstclear(t_str_list **lst)
{
	if (!lst || !*lst)
		return ;
	if ((*lst)->next)
		lstclear(&((*lst)->next));
	free(*lst);
	*lst = NULL;
	return ;
}
