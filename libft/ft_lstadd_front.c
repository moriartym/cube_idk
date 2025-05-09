/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfasius <dfasius@student.42.sg>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 16:18:08 by dfasius           #+#    #+#             */
/*   Updated: 2024/05/18 17:19:54 by dfasius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (!lst || !new)
		return ;
	new->next = *lst;
	*lst = new;
}
/*
#include <stdio.h>

int	main(void)
{
	t_list test1 = {.content = "hello1", .next = NULL};
	t_list test2 = {.content = "hello2", .next = NULL};

	t_list *testp = &test1;
	t_list **lst = &testp;

	t_list *new = &test2;
	ft_lstadd_front(lst,new);

	printf("%s", (char *) (*lst)->content);
}
*/
