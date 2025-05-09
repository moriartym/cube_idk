/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfasius <dfasius@student.42.sg>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 15:13:35 by dfasius           #+#    #+#             */
/*   Updated: 2024/05/31 15:14:12 by dfasius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

typedef struct s_glist
{
	char			*content;
	struct s_glist	*next;
}	t_glist;

int		search_newline(t_glist *list);
int		string_length(t_glist *list);
char	*string_malloc(t_glist *list, char *str, int len);
void	clear_node(t_glist **lst);
int		save_string(t_glist **list);
char	*create_string(t_glist **list, int fd);
char	*get_next_line(int fd);
char	*create_string_helper(t_glist **list);
int		addback_new_node(t_glist **lst, char **content);
int		save_string_helper(int i, int j, char *content, t_glist **list);

#endif
