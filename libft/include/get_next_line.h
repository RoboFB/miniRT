/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 16:51:43 by rgohrig           #+#    #+#             */
/*   Updated: 2025/04/23 14:45:58 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <unistd.h>
# include <stdlib.h>

typedef struct s_str_list
{
	char				str[BUFFER_SIZE];
	size_t				len;
	struct s_str_list	*next;
}							t_str_list;

char			*get_next_line(int fd);
void			add_node_to_end(t_str_list **lst, t_str_list *new);
t_str_list		*make_node(char *str, size_t len);
size_t			len_all_str(t_str_list *lst);
void			lstclear(t_str_list **lst);

#endif