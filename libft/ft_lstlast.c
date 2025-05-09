/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfasius <dfasius@student.42.sg>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 16:34:24 by dfasius           #+#    #+#             */
/*   Updated: 2024/05/19 14:50:35 by dfasius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (0);
	while (lst->next)
	{
		lst = lst->next;
	}
	return (lst);
}
/*
#include <stdio.h>
int	main(void)
{
	t_list test5 = {.content = "hello5", .next = 0};
	t_list test4 = {.content = "hello4", .next = &test5};
	t_list test3 = {.content = "hello3", .next = &test4};
	t_list test2 = {.content = "hello2", .next = &test3};
	t_list test1 = {.content = "hello1", .next = &test2};

	printf("%s",(char *) (ft_lstlast(&test1))->content);
}
*/
