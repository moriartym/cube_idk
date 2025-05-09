/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfasius <dfasius@student.42.sg>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 16:53:59 by dfasius           #+#    #+#             */
/*   Updated: 2024/05/18 17:21:02 by dfasius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
#include <stdlib.h>
/*
void	ft_del(void *content)
{
	free(content);
}
*/

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*next_node;

	while (*lst)
	{
		next_node = (*lst)->next;
		del((*lst)->content);
		free(*lst);
		*lst = next_node;
	}
	*lst = 0;
}
/*
#include <stdio.h>
#include <string.h>
int	main(void)
{
	t_list *test2;
	char *str2;

	str2 = (char *) malloc (sizeof(char) * 6);
	test2 = (t_list *) malloc (sizeof(t_list));

	strcpy(str2, "hello");
	test2->content = str2;
	test2->next = 0;


	t_list *test;
        char *str;

        str = (char *) malloc (sizeof(char) * 6);
        test = (t_list *) malloc (sizeof(t_list));

        strcpy(str, "hello");
        test->content = str;
        test->next = test2;

	ft_lstclear(&test, &ft_del);

	if (!test)
	{
		printf("ok");
	}
}
*/
