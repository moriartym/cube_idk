/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfasius <dfasius@student.42.sg>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 14:50:24 by dfasius           #+#    #+#             */
/*   Updated: 2024/05/31 18:33:13 by dfasius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*string_malloc(t_glist *list, char *str, int len)
{
	int		i;
	int		j;
	t_glist	*temp;

	temp = list;
	i = 0;
	while (len > 0 && temp)
	{
		j = 0;
		while ((temp->content)[j] && len > 0)
		{
			str[i++] = (temp->content)[j++];
			len--;
		}
		temp = temp->next;
	}
	str[i] = '\0';
	return (str);
}

int	search_newline(t_glist *list)
{
	int		i;
	t_glist	*temp;

	temp = list;
	while (temp)
	{
		i = 0;
		while ((temp->content)[i])
		{
			if ((temp->content)[i] == '\n')
				return (1);
			i++;
		}
		temp = temp->next;
	}
	return (0);
}

char	*create_string_helper( t_glist **list)
{
	int		len;
	char	*str;

	len = string_length(*list);
	str = (char *) malloc (sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	str = string_malloc(*list, str, len);
	return (str);
}

char	*create_string(t_glist **list, int fd)
{
	char	*buffer;
	int		bytes_size;

	bytes_size = 0;
	while (!search_newline(*list))
	{
		buffer = (char *) malloc (sizeof(char) * (BUFFER_SIZE + 1));
		if (!buffer)
			return (NULL);
		bytes_size = read(fd, buffer, BUFFER_SIZE);
		if (bytes_size <= 0)
		{
			free(buffer);
			break ;
		}
		buffer[bytes_size] = '\0';
		if (addback_new_node (list, &buffer) == 0)
			return (NULL);
	}
	if (!(*list) || bytes_size == -1)
		return (NULL);
	return (create_string_helper(list));
}

char	*get_next_line(int fd)
{
	t_glist			*list;
	char			*final_string;
	int				save;

	list = NULL;
	if (fd < 0 || fd > 4095 || BUFFER_SIZE <= 0)
		return (clear_node(&list), NULL);
	final_string = create_string(&list, fd);
	if (!final_string)
	{
		clear_node(&list);
		return (NULL);
	}
	save = save_string (&list);
	if (save == 0)
	{
		free(final_string);
		clear_node(&list);
		return (NULL);
	}
	return (final_string);
}
