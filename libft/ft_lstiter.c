/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfasius <dfasius@student.42.sg>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 17:01:42 by dfasius           #+#    #+#             */
/*   Updated: 2024/05/18 17:21:31 by dfasius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
/*
void	ft_content(void *content)
{
	char	*contentchar;

	contentchar = content;
	if (((contentchar[5]) - 48 ) % 2 == 0)
		printf("even\n");
}
*/
void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	while (lst)
	{
		f(lst->content);
		lst = lst->next;
	}
}
/*
#include <stdio.h>
int     main(void)
{
        t_list test5 = {.content = "hello5", .next = 0};
        t_list test4 = {.content = "hello4", .next = &test5};
        t_list test3 = {.content = "hello3", .next = &test4};
        t_list test2 = {.content = "hello2", .next = &test3};
        t_list test1 = {.content = "hello1", .next = &test2};

	ft_lstiter(&test1, &ft_content);
}
*/
