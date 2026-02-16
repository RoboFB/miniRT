/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 16:56:39 by rgohrig           #+#    #+#             */
/*   Updated: 2026/02/16 16:21:48 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// F: Malloc   R: (*str)OK (NULL)errorM
static
char	*make_line(t_str_list **start_lst)
{
	size_t			idx_out;
	size_t			idx_content;
	t_str_list		*lst;
	char			*out;

	idx_out = 0;
	lst = *start_lst;
	out = malloc((len_all_str(lst) + 1) * sizeof(char));
	if (!out)
		return (NULL);
	while (lst)
	{
		idx_content = 0;
		while (lst->len > idx_content)
			out[idx_out++] = lst->str[idx_content++];
		lst = lst->next;
	}
	out[idx_out++] = '\0';
	return (out);
}

// F: Malloc   R: (0)OK \n found (1)OK end of buffer (-1)errorM
static
int	save_buffer(char *buffer, t_str_list **lst_start, size_t len)
{
	size_t			idx_buffer;
	t_str_list		*node;
	int				out;

	out = 1;
	node = make_node("", 0);
	if (!node)
		return (-1);
	idx_buffer = 0;
	while (idx_buffer < len && out == 1)
	{
		if (buffer[idx_buffer] != '\0')
		{
			node->str[node->len] = buffer[idx_buffer];
			node->len++;
			if (buffer[idx_buffer] == '\n')
				out = 0;
		}
		buffer[idx_buffer] = '\0';
		idx_buffer++;
	}
	add_node_to_end(lst_start, node);
	return (out);
}

// F: Malloc, Read  R: (0)OK one line   (-1..-3)error
static
int	read_line(int fd, char *buffer, t_str_list **lst_start)
{
	ssize_t			len;
	int				run;

	len = BUFFER_SIZE;
	run = 1;
	while (run == 1)
	{
		run = save_buffer(buffer, lst_start, len);
		if (run < 0)
			return (-1);
		else if (run == 0)
			return (0);
		len = read(fd, buffer, BUFFER_SIZE);
		if (len < 0)
			return (-2);
		else if (len == 0 && len_all_str(*lst_start) == 0)
			return (-3);
		else if (len == 0 && len_all_str(*lst_start) != 0)
			return (0);
	}
	return (-1);
}

// F: Malloc   R: (*str)OK one line   (NULL)error or end of file
char	*get_next_line(int fd)
{
	static char		buffer[BUFFER_SIZE];
	char			*out;
	t_str_list		*lst_start;

	out = NULL;
	lst_start = NULL;
	if (0 > fd)
		return (NULL);
	if (read_line(fd, buffer, &lst_start) == 0)
		out = make_line(&lst_start);
	lstclear(&lst_start);
	return (out);
}
